Dim control_bucle As Byte
Dim display As Byte
control_bucle = 0
TRISD = 0
TRISA = %11111011
PORTA = %00000100
main:
	Gosub calculadisplay
	PORTD = display
	WaitMs 1000
	control_bucle = control_bucle + 1
	If control_bucle = 8 Then
		control_bucle = 0
	Endif
	Goto main
	End
calculadisplay:
	If control_bucle = 0 Then
		display = %00000001
	Else
		display = ShiftLeft(display, 1)
	Endif
Return                                            