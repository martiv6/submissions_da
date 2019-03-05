;
; 2A_Task2_asm.asm
;
; Created: 3/2/2019 12:20:24 PM
; Author : victor
;

.org 0

	SBI	DDRB, 0b0010		; makes PB2 the output 
	CBI	DDRC, 0b0000		; makes A1/S1 the button to  push
	SBI	PORTB, 0b0010		; makes PB2 turn off 

THEWAIT:	
	SBIC	PINC, 0b0001	; if pressed do this
	RJMP	THEWAIT			; if not pressed jump back to THEWAIT
	RCALL	THEPUSH			; keeps led to 1.25s

SLOWDOWN:
	LDS	R29, TCNT1H			; load upper bytes of timer counter to r29
	LDS	R28, TCNT1L 		; load lower bytes of timer counter to r28
	CPI	R28, 0x4A			; check to see if lower 8 bits of timer counter are valid
	BRSH	WELP			; if same or higher if not goes back to welp
	RJMP	SLOWDOWN		; otherwise keep checking lower bytes

THEPUSH:
	CBI		PORTB, 0b0010	; if pressed it will light up the led
	LDI		R20, 0b0101	    ; set the prescalar to 1024
	STS		TCCR1B, R20		; loads value to R20
	LDI		R20, 0b0000		; resets timer
	STS		TCNT1H, R20		; clears value in TCNT1H
	STS		TCNT1L, R20 	; clears value in TCNT1L
	RJMP	SLOWDOWN		; jumos down to SLOWDOWN to start again

COMINGHOME:
	RJMP	THEWAIT			; goes to back to see in theres an input
	SBI		PORTB, 0b0010	; if on display on LED
	RJMP	THEWAIT			; goes back to see if there is an input

WELP:	
	CPI	R29, 0x4C			; check if upper timer counter have reached desired value
	BRLT	SLOWDOWN		; otherwise recheck the lower bytes
	SBI	PORTB, 0b0010		; TURN OFF LED
	RET	