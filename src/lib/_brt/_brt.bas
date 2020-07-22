'
' _brt: BASIC runtime, minimal core needed to support the compiler's generated code
'

OPTION EXPLICIT
OPTION PRIVATE

' ERROR codes

PUBLIC EXTERN ERR AS INTEGER

PUBLIC CONST AS INTEGER ERR_OUT_OF_MEMORY =  7

PUBLIC DECLARE SUB _debug_puts (s AS STRING)
PUBLIC DECLARE SUB _debug_puts2(s AS INTEGER)

' AmigaOS library bases

PUBLIC EXTERN SysBase AS VOID PTR
PUBLIC EXTERN DOSBase AS VOID PTR
PUBLIC EXTERN MathTransBase AS VOID PTR

' math support

PUBLIC DECLARE FUNCTION fix   (f AS SINGLE) AS INTEGER
PUBLIC DECLARE FUNCTION int   (f AS SINGLE) AS INTEGER
PUBLIC DECLARE FUNCTION cint  (f AS SINGLE) AS INTEGER
PUBLIC DECLARE FUNCTION clng  (f AS SINGLE) AS LONG

PUBLIC CONST AS SINGLE PI = 3.14159

PUBLIC DECLARE FUNCTION ATN (f AS SINGLE) AS SINGLE LIB  -30 MathTransBase (d0)
PUBLIC DECLARE FUNCTION SIN (f AS SINGLE) AS SINGLE LIB  -36 MathTransBase (d0)
PUBLIC DECLARE FUNCTION COS (f AS SINGLE) AS SINGLE LIB  -42 MathTransBase (d0)
PUBLIC DECLARE FUNCTION TAN (f AS SINGLE) AS SINGLE LIB  -48 MathTransBase (d0)
PUBLIC DECLARE FUNCTION EXP (f AS SINGLE) AS SINGLE LIB  -78 MathTransBase (d0)
PUBLIC DECLARE FUNCTION LOG (f AS SINGLE) AS SINGLE LIB  -84 MathTransBase (d0)
PUBLIC DECLARE FUNCTION SQR (f AS SINGLE) AS SINGLE LIB  -96 MathTransBase (d0)
PUBLIC DECLARE FUNCTION ASIN(f AS SINGLE) AS SINGLE LIB -114 MathTransBase (d0)
PUBLIC DECLARE FUNCTION ACOS(f AS SINGLE) AS SINGLE LIB -120 MathTransBase (d0)

' STR$ support

PUBLIC DECLARE FUNCTION _s1toa   (b AS BYTE    ) AS STRING
PUBLIC DECLARE FUNCTION _s2toa   (i AS INTEGER ) AS STRING
PUBLIC DECLARE FUNCTION _s4toa   (l AS LONG    ) AS STRING
PUBLIC DECLARE FUNCTION _u1toa   (b AS UBYTE   ) AS STRING
PUBLIC DECLARE FUNCTION _u2toa   (i AS UINTEGER) AS STRING
PUBLIC DECLARE FUNCTION _u4toa   (l AS ULONG   ) AS STRING
PUBLIC DECLARE FUNCTION _ftoa    (f AS SINGLE  ) AS STRING
PUBLIC DECLARE FUNCTION _booltoa (b AS BOOLEAN ) AS STRING

' string utils

PUBLIC DECLARE FUNCTION len   (s AS STRING) AS LONG
PUBLIC DECLARE FUNCTION chr$  (i AS INTEGER)

' dynamic memory

PUBLIC DECLARE FUNCTION allocate (size AS ULONG, flags AS ULONG=0) AS VOID PTR

' misc

PUBLIC DECLARE SUB _aqb_assert (b AS BOOLEAN, s AS STRING)
PUBLIC DECLARE SUB _aqb_error (i AS INTEGER)
PUBLIC DECLARE SUB _aqb_resume_next
PUBLIC DECLARE SUB _aqb_on_exit_call (p AS SUB)
PUBLIC DECLARE SUB _aqb_on_error_call (p AS SUB)

PUBLIC DECLARE FUNCTION TIMER() AS SINGLE

PUBLIC CONST AS VOID PTR NULL = 0

PUBLIC EXTERN g_stdout AS VOID PTR

