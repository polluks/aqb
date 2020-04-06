
// playground to try various functions offered by this library

#include "aio.h"
#include "autil.h"
#include "astr.h"
#include "awindow.h"

#include <clib/mathffp_protos.h>
#include <clib/mathtrans_protos.h>

#include <exec/types.h>
#include <exec/memory.h>
#include <clib/exec_protos.h>

FLOAT __mod_ffp(FLOAT divident, FLOAT divisor);

extern int foo (void);
extern SHORT fooW (void);

extern void assertW(SHORT w, const char *msg);
extern void assertC(char b, const char *msg);

void clibtestmain (void)
{
    ULONG l, m;
    FLOAT a, b;

    _aio_puts("clibtestmain\n");

    l = 0x80000047;
    m = 0x80000147;

    a = *((FLOAT*) &l);
    b = *((FLOAT*) &m);

    _aio_puts("a: "); _aio_putf(a); _aio_putnl();
    _aio_puts("b: "); _aio_putf(b); _aio_putnl();

    // _aqb_assert (foo() == 42, "this should fail.");
    // assertC (foo() == 42, "this should fail.");
    // assertW (fooW(), "this should fail.");

    // assertEqualsLong (10, 10, "this shouldn't have failed.");
    // assertEqualsLong (10, 42, "this should fail.");

    // a = SPFlt(23);
    // b = SPFlt(42);

    // assertEqualsSingle (a, a, "this shouldn't have failed.");
    // assertEqualsSingle (a, b, "this should fail.");

    _aio_puts("FAIL: this should never be executed.\n");
#if 0
    FLOAT a, b, c, d, e, f;
    LONG l;

    __aqb_line (1, 2, 3, 4, 255, 6);

    // window(1, "AQB Main Window", 0, 0, 619, 189, AW_FLAG_SIZE | AW_FLAG_DRAG | AW_FLAG_DEPTH | AW_FLAG_CLOSE | AW_FLAG_REFRESH, 0);
    // __aqb_window_open(1, "AQB Main Window", -1, -1, -1, -1, AW_FLAG_SIZE | AW_FLAG_DRAG | AW_FLAG_DEPTH | AW_FLAG_CLOSE | AW_FLAG_REFRESH, 0);

    // __aqb_line (30, 30, 50, 60,  AW_LINE_FLAG_BOX, 0);
    // __aqb_line (130, 130, 150, 160, AW_LINE_FLAG_BOX | AW_LINE_FLAG_FILL, 0);
    // __aqb_line (300, 10, 400, 100, 0, 0);
    // __aqb_line (310, 10, 410, 100, 0, 0);

    _aio_puts("clibtestmain:\n");
    _aio_puts("puts4: "); _aio_puts4(12345678); _aio_putnl();
    _aio_puts("puts2: "); _aio_puts2(12345); _aio_putnl();

    for (i=0; i<100; i++)
    {
        // _aio_puts("i="); _aio_puts2(i); _aio_putnl();
        // __aqb_line (i, i*2, i*3, i*4, i*5, i*6);
        __aqb_line (i*5, 0, 320, 200, 0, 0);
    }

    a = SPFlt(23);
    b = SPFlt(42);
    c = SPDiv(a, b);
    d = SPMul(b, c);
    e = SPFlt(7);
    f = SPFlt(2);

    _aio_puts("a: "); _aio_puts4(SPFix(a));
    _aio_puts(", b: "); _aio_puts4(SPFix(b));
    _aio_puts(", c = a/b: "); _aio_puts4(SPFix(c));
    _aio_puts(", d = b*c: "); _aio_puts4(SPFix(d));
    _aio_puts(", b-a: "); _aio_puts4(SPFix(SPSub(b, a)));
    _aio_puts(", a-b: "); _aio_puts4(SPFix(SPSub(a, b)));
    _aio_puts(", e: "); _aio_puts4(SPFix(e));
    _aio_puts(", f: "); _aio_puts4(SPFix(f));
    _aio_putnl();


    e = SPMul(SPFlt(68000), SPFlt(10000));

    _aio_puts("a: "); _aio_putf(a); _aio_putnl();
    _aio_puts("b: "); _aio_putf(b); _aio_putnl();
    _aio_puts("c: "); _aio_putf(c); _aio_putnl();
    _aio_puts("d: "); _aio_putf(d); _aio_putnl();
    _aio_puts("e: "); _aio_putf(e); _aio_putnl();
    _aio_puts("f: "); _aio_putf(f); _aio_putnl();
    _aio_puts("-1/3: "); _aio_putf(SPDiv(SPFlt(-1), SPFlt(3))); _aio_putnl();
    _aio_puts("27 MOD 11: "); _aio_putf(__mod_ffp(SPFlt(27), SPFlt(11))); _aio_putnl();

    l = SPFix(c);

    if (l>42)
    {
        _aio_puts("foo"); _aio_putnl();
    }
    else
    {
        _aio_puts("bar"); _aio_putnl();
    }
#endif

    //delay(5);
}
