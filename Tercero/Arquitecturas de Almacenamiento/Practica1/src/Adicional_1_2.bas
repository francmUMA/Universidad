Dim segmento As Byte
Dim display As Byte
Dim lcd As Byte
lcd = 0
display = 0
segmento = 0
TRISD = 0
TRISA = %11000011
PORTA = %00000100
main:
	Gosub calculadisplay
	PORTD = display
	WaitMs 1000
	segmento = segmento + 1
	If segmento = 8 Then
		segmento = 0
		lcd = lcd + 1
		PORTA = ShiftLeft(PORTA, 1)
		If lcd = 4 Then
			lcd = 0
			PORTA = %00000100
		Endif
	Endif
	
	Goto main
	End
calculadisplay:
	If segmento = 0 Then
		display = %00000001
	Else
		display = ShiftLeft(display, 1)
	Endif
Return                                            