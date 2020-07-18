'
' _brt: BASIC runtime, minimal core needed to support the compiler's generated code
'

OPTION EXPLICIT
OPTION PRIVATE

' ERROR codes

PUBLIC EXTERN ERR AS INTEGER

CONST AS INTEGER ERR_OUT_OF_MEMORY =  7

PUBLIC DECLARE SUB _debug_puts (s AS STRING)
PUBLIC DECLARE SUB _debug_puts2(s AS INTEGER)

' math support

PUBLIC DECLARE FUNCTION fix   (f AS SINGLE) AS INTEGER
PUBLIC DECLARE FUNCTION int   (f AS SINGLE) AS INTEGER
PUBLIC DECLARE FUNCTION cint  (f AS SINGLE) AS INTEGER
PUBLIC DECLARE FUNCTION clng  (f AS SINGLE) AS LONG
PUBLIC DECLARE FUNCTION len   (s AS STRING) AS LONG

' STR$ support

PUBLIC DECLARE FUNCTION _s1toa   (b AS BYTE    ) AS STRING
PUBLIC DECLARE FUNCTION _s2toa   (i AS INTEGER ) AS STRING
PUBLIC DECLARE FUNCTION _s4toa   (l AS LONG    ) AS STRING
PUBLIC DECLARE FUNCTION _u1toa   (b AS UBYTE   ) AS STRING
PUBLIC DECLARE FUNCTION _u2toa   (i AS UINTEGER) AS STRING
PUBLIC DECLARE FUNCTION _u4toa   (l AS ULONG   ) AS STRING
PUBLIC DECLARE FUNCTION _ftoa    (f AS SINGLE  ) AS STRING
PUBLIC DECLARE FUNCTION _booltoa (b AS BOOLEAN ) AS STRING

' dynamic memory

PUBLIC DECLARE FUNCTION allocate (size AS ULONG, flags AS ULONG=0) AS VOID PTR

' AmigaOS library bases

PUBLIC EXTERN SysBase AS VOID PTR
PUBLIC EXTERN DOSBase AS VOID PTR
PUBLIC EXTERN MathTransBase AS VOID PTR

' misc

PUBLIC DECLARE SUB _aqb_assert (b AS BOOLEAN, s AS STRING)

PUBLIC DECLARE SUB _aqb_error (i AS INTEGER)
PUBLIC DECLARE SUB _aqb_resume_next
PUBLIC DECLARE SUB _aqb_on_exit_call (p AS SUB)
PUBLIC DECLARE SUB _aqb_on_error_call (p AS SUB)

PUBLIC CONST AS VOID PTR NULL = 0

PUBLIC EXTERN g_stdout AS VOID PTR

