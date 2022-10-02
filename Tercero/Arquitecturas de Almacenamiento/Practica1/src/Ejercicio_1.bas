Dim control_bucle As Byte
Dim display As Byte
control_bucle = 0
TRISB = 0
main:
	display = control_bucle
	Gosub calculadisplay
	PORTB = display
	control_bucle = control_bucle + 1
	If control_bucle = 10 Then
		control_bucle = 0
	Endif
	Goto main
	End
calculadisplay:
	Select Case display
	Case 0
		display = %00111111
	Case 1
		display = %00000110
	Case 2
		display = %01011011
	Case 3
		display = %01001111
	Case 4
		display = %01100110
	Case 5
		display = %01101101
	Case 6
		display = %01111101
	Case 7
		display = %00000111
	Case 8
		display = %01111111
	Case 9
		display = %01100111
	EndSelect
Return                                            

	
