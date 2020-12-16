#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "assem.h"
#include "frame.h"
#include "graph.h"
#include "color.h"
#include "flowgraph.h"
#include "liveness.h"
#include "regalloc.h"
#include "table.h"
#include "errormsg.h"
#include "options.h"

// #define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
static Temp_map g_debugTempMap;
#endif

static UG_node temp2Node(Temp_temp t, UG_graph g)
{
    if (t == NULL)
        return NULL;
    UG_nodeList nodes = g->nodes;
    UG_nodeList p;
    for (p=nodes; p!=NULL; p=p->tail)
    {
        if (Live_gtemp(p->head)==t)
            return p->head;
    }
    return NULL;
}

static Temp_temp node2Temp(UG_node n)
{
    if (n == NULL)
        return NULL;
    return Live_gtemp(n);
}

static UG_node getAlias(UG_node n, UG_table aliases, Temp_tempSet coalescedNodes)
{
    Temp_temp t = node2Temp(n);
    if (Temp_tempSetContains(coalescedNodes, t))
    {
        UG_node alias = (UG_node)UG_look(aliases, n);
        return getAlias(alias, aliases, coalescedNodes);
    }
    else
    {
        return n;
    }
}

static Temp_temp aliasedSpilled(Temp_temp t, UG_graph ig, UG_table aliases, Temp_tempSet coalescedNodes, Temp_tempSet spilled)
{
    if (!Temp_tempSetContains(spilled, t))
        return NULL;
    UG_node n = temp2Node(t, ig);
    assert(n);
    getAlias(n, aliases, coalescedNodes);
    t = node2Temp(n);
    assert(t);
    return t;
};

struct RA_result RA_regAlloc(F_frame f, AS_instrList il)
{
    struct RA_result  ret = {NULL, NULL};

    FG_graph          flow;
    Live_graph        live;
    struct COL_result col;

#ifdef ENABLE_DEBUG
    g_debugTempMap = Temp_layerMap(F_initialRegisters(), Temp_getNameMap());
#endif

    int try = 0;
    while (++try < 7)
    {
        if (OPT_get(OPTION_VERBOSE))
        {
            printf("regalloc try #%d, running before liveness        : ", try);
            U_memstat();
        }

        Temp_map initialRegs = F_initialRegisters();

        flow = FG_AssemFlowGraph(il, f);
#ifdef ENABLE_DEBUG
        printf("try #%d flow graph:\n", try);
        printf("-----------------------\n");
        FG_show(stdout, flow, g_debugTempMap);
#endif

        live = Live_liveness(flow);
#ifdef ENABLE_DEBUG
        printf("try #%d liveness graph:\n", try);
        printf("-----------------------\n");
        // G_show(stdout, G_nodes(live.graph), sprintTemp);
        Live_showGraph(stdout, live, g_debugTempMap);
#endif

        if (OPT_get(OPTION_VERBOSE))
        {
            printf("regalloc try #%d, after liveness before COL_color: ", try);
            U_memstat();
        }

        col = COL_color(live, initialRegs, F_registers());

        if (Temp_tempSetIsEmpty(col.spills))
        {
            break;
        }

        Temp_tempSet spilled = col.spills;

        // Assign locals in memory
        TAB_table spilledLocal = TAB_empty();
        for (Temp_tempSetNode tn = spilled->first; tn; tn = tn->next)
        {
            F_access acc;
            if (f)
            {
                acc = F_allocLocal(f, Temp_ty(tn->temp));
            }
            else
            {
                Temp_label name = Temp_namedlabel(strprintf("__spilledtemp_%06d", Temp_num(tn->temp)));
                acc = F_allocGlobal(name, Temp_ty(tn->temp));
            }

            TAB_enter(spilledLocal, tn->temp, acc);
        }

        // modify instruction list, insert move instructions for spilled temps
        AS_instrListNode an = il->first;
        while (an)
        {
            AS_instr inst = an->instr;
            Temp_temp useSpilled = aliasedSpilled(inst->src, live->graph, col.alias, col.coalescedNodes, spilled);
            Temp_temp defSpilled = aliasedSpilled(inst->dst, live->graph, col.alias, col.coalescedNodes, spilled);

            if (useSpilled)
            {
                F_access local = (F_access)TAB_look(spilledLocal, useSpilled);
                AS_instrListInsertBefore (il, an,                                                       // move.x localOffset(fp), useSpilled
                                          AS_InstrEx(AS_MOVE_Ofp_AnDn, AS_tySize(Temp_ty(useSpilled)),
                                                     NULL, useSpilled, 0, F_accessOffset(local), NULL));
            }

            if (defSpilled)
            {
                F_access local = (F_access)TAB_look(spilledLocal, defSpilled);
                AS_instrListInsertAfter (il, an,                                                        // move.x defSpilled, localOffset(FP)
                                         AS_InstrEx(AS_MOVE_AnDn_Ofp, AS_tySize(Temp_ty(defSpilled)),
                                                    defSpilled, NULL, 0, F_accessOffset(local), NULL));
                an = an->next;
            }

            an = an->next;
        }
    }

    if (!Temp_tempSetIsEmpty(col.spills))
    {
        EM_error(0, "failed to allocate registers");
    }

    if (OPT_get(OPTION_VERBOSE))
    {
        printf("regalloc succeeded:                               ");
        U_memstat();
    }

    //if (col.coalescedMoves != NULL)
    {

        // filter out coalesced moves, NOPs

#ifdef ENABLE_DEBUG
        Temp_map colTempMap = Temp_layerMap(col.coloring, g_debugTempMap);
        printf("/* coalesced: moves:\n");
        AS_printInstrSet (stdout, col.coalescedMoves, colTempMap);
        printf("*/\n");
#endif

        AS_instrListNode an = il->first;
        while (an)
        {
            AS_instr inst = an->instr;

            // remove coalesced moves
            if (AS_instrSetContains(col.coalescedMoves, inst))
            {
#ifdef ENABLE_DEBUG
                char buf[256];
                AS_sprint(buf, inst, colTempMap);
                printf("/* coalesced: %s */\n", buf);
#endif
                AS_instrListRemove (il, an);
                an = an->next;
                continue;
            }
            else
            {
                // remove NOPs
                if (inst->mn == AS_NOP)
                {
#ifdef ENABLE_DEBUG
                    printf("/* NOP */\n");
#endif
                    AS_instrListRemove (il, an);
                    an = an->next;
                    continue;
                }
                else
                {
#ifdef ENABLE_DEBUG
                    char buf[256];
                    AS_sprint(buf, inst, colTempMap);
                    printf("%s\n", buf);
#endif
                }
            }
            an = an->next;
        }
    }

    ret.coloring = col.coloring;
    ret.il = il;

#ifdef ENABLE_DEBUG
    printf("register coloring map:\n");
    printf("----------------------\n");
    Temp_dumpMap(stdout, ret.coloring);
#endif
    return ret;
}

