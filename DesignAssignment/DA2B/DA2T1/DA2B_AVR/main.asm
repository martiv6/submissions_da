;
; DA2B_AVR.asm
;
; Created: 3/9/2019 11:32:16 AM
; Author : victor
;


.ORG 0
	JMP 	MAIN

.ORG 0b0010		 				; LOCATION FOR EXTERNAL INTERRUPT 0
	JMP 	EX0_ISR
	
MAIN: 
	LDI 	R20, HIGH(RAMEND)	; loads value to R20 upper bits
	OUT 	SPH, R20			; loads the value from R20 into SP upper
	LDI 	R20, LOW(RAMEND)	; loads value to R20 lower bits
	OUT 	SPL, R20 			; starts stack	
	LDI		R17, 0xFF			; to have the led off
	LDI 	R20, 0X02 			; makes INT0 falling edge triggered
	STS		EICRA, R20 			; external interrupt control
	SBI 	DDRB, 0b0010 		; makes pd5 the output
	CBI		PORTB, 0b0101		; clears the bits in pd5
	SBI 	DDRD, 0b0010		; setting as an output 
	SBI		PORTD, 0b0010		; enables the pull up
	LDI 	R20, 1<<INT0 		; INT0 enabled
	OUT 	EIMSK, R20 			; External interrupt register
	SEI 						; enable the interrupt

Hello: 
	out PORTB, R17				; makes sure the led is off 
	JMP Hello					; waits for the interrupt


EX0_ISR:
	SBI	PORTB, 2				; outputs to the led
	CBI	PORTB, 2				; clears the value in the led
	LDI  R18, 0x2C				; does delay
    LDI  R19, 0xC8
    LDI  R20, 0xFA
L1: DEC  R20
    BRNE L1
    DEC  R19
    BRNE L1
    DEC  R18
    BRNE L1
	RETI						; starts over

