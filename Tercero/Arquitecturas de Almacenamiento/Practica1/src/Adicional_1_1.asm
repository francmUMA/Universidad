; Compiled with: PIC Simulator IDE v8.158
; Microcontroller model: PIC16F877A
; Clock frequency: 4.0MHz
;
	R0L EQU 0x020
	R0H EQU 0x021
	R4L EQU 0x028
	R4H EQU 0x029
	R0HL EQU 0x020
	R4HL EQU 0x028
;       The address of 'control_bucle' (byte) (global) is 0x022
;       The address of 'display' (byte) (global) is 0x023
	ORG 0x0000
	BCF PCLATH,3
	BCF PCLATH,4
	GOTO L0003
	ORG 0x0004
	RETFIE
; User code start
L0003:
; 1: Dim control_bucle As Byte
; 2: Dim display As Byte
; 3: control_bucle = 0
	CLRF 0x022
; 4: TRISD = 0
	BSF STATUS,RP0
	CLRF TRISD
	BCF STATUS,RP0
; 5: TRISA = %11111011
	MOVLW 0xFB
	BSF STATUS,RP0
	MOVWF TRISA
	BCF STATUS,RP0
; 6: PORTA = %00000100
	MOVLW 0x04
	MOVWF PORTA
; 7: main:
L0001:
; 8: Gosub calculadisplay
	CALL L0002
; 9: PORTD = display
	MOVF 0x023,W
	MOVWF PORTD
; 10: WaitMs 1000
	MOVLW 0xE8
	MOVWF R0L
	MOVLW 0x03
	MOVWF R0H
	CALL W001
; 11: control_bucle = control_bucle + 1
	INCF 0x022,F
; 12: If control_bucle = 8 Then
	MOVF 0x022,W
	SUBLW 0x08
	BTFSS STATUS,Z
	GOTO L0004
; 13: control_bucle = 0
	CLRF 0x022
; 14: Endif
L0004:
; 15: Goto main
	GOTO L0001
; 16: End
L0005:	GOTO L0005
; 17: calculadisplay:
L0002:
; 18: If control_bucle = 0 Then
	MOVF 0x022,W
	SUBLW 0x00
	BTFSS STATUS,Z
	GOTO L0006
; 19: display = %00000001
	MOVLW 0x01
	MOVWF 0x023
; 20: Else
	GOTO L0007
L0006:
; 21: display = ShiftLeft(display, 1)
	MOVF 0x023,W
	MOVWF R0L
	CLRF R0H
	MOVLW 0x01
	CALL SL00
	MOVF R0L,W
	MOVWF 0x023
; 22: Endif
L0007:
; 23: Return
	RETURN
; End of user code
L0008:	GOTO L0008
;
;
; Delay Routine Byte
; minimal routine execution time: 8탎
; routine execution time step: 3탎
; maximal routine execution time: 770탎
DL01:
	DECFSZ R4L,F
	GOTO DL01
	RETURN
; Delay Routine Word
; minimal routine execution time: 15탎
; routine execution time step: 10탎
; maximal routine execution time: 655365탎
DL02:
	MOVLW 0x01
	SUBWF R4L,F
	CLRW
	BTFSS STATUS,C
	ADDLW 0x01
	SUBWF R4H,F
	BTFSS STATUS,C
	RETURN
	GOTO DL02
; Waitms Routine
W001:	MOVLW 0x01
	SUBWF R0L,F
	CLRW
	BTFSS STATUS,C
	ADDLW 0x01
	SUBWF R0H,F
	BTFSS STATUS,C
	RETURN
	MOVLW 0x61
	MOVWF R4L
	MOVLW 0x00
	MOVWF R4H
	CALL DL02
	GOTO W001
;
;
; Word ShiftLeft Routine
SL01:	BCF STATUS,C
	RLF R0L,F
	RLF R0H,F
SL00:	ADDLW 0xFF
	BTFSC STATUS,C
	GOTO SL01
	RETURN
;
;
; End of listing
	END
