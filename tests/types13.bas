'
' OOP Test 1
'

OPTION EXPLICIT

TYPE mycontainer

    o AS VOID PTR

    DECLARE SUB store (o AS VOID PTR)
    DECLARE FUNCTION retrieve () AS VOID PTR

END TYPE

DIM o AS mycontainer

' mycontainer.store(17)
' PRINT mycontainer.retrieve()

