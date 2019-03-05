;
; 2A_task_1.asm
;
; Created: 3/1/2019 8:18:16 PM
; Author : victor
;

.org 0
  
	LDI		r16, 0b0111		; setting pd2
	OUT		DDRB, r16		; enableing pd2 as output
	LDI		r17, 0b0000		; used to set/reset pd5
	LDI		r20, 0b0101		; setting up TCCR1B = 00000101 for 1024
	STS		TCCR1B,	r20		; storing the value in TCCR1B

INTRO:
	LDI		r20, 0b0000		; setting up timer counter to 0
	STS		TCNT1H, r20 	; Timer counter is 16 bits
	STS		TCNT1L, r20 	; Thus, requires 2 8 bit regs
	RJMP	SLOWDOWN 		; jumps back to SLOWDOWN

COMEBACK:
	EOR		r17, r16		; xor to toggle LED
	OUT		PORTB, r17		; enable pd5
	LDI		r20, 0b0000		; setting up timer counter to 0
	STS		TCNT1H, r20 	; Timer counter is 16 bits
	STS		TCNT1L, r20 	; Thus, requires 2 8 bit regs
	RJMP	FINAL_STOP		; Jumps to FINAL_STOP

COMEBACK_DOS:
	EOR		r17, r16		; xor to toggle LED
	OUT		PORTB, r17		; enable pd5
	RJMP	INTRO			; repeat main loop

SHOWDOWN_1:
	CPI		r29, 0x11		; check if upper timer counter have reached desired value
	BRLT	SLOWDOWN		; otherwise recheck the upper bytes
	RJMP	COMEBACK		; jumps to COMEBACK

SLOWDOWN:
	LDS		r29, TCNT1H		; load upper bytes of timer counter to r29
	LDS		r28, TCNT1L 	; load lower bytes of timer counter to r28
	CPI		r28, 0xB2		; check to see if lower 8 bits of timer counter 
	BRSH	SHOWDOWN_1		; if lower bit not
	RJMP	SLOWDOWN		; otherwise keep checking lower bytes

SHOWDOWN_2:
	CPI		r29, 0x1A		; check if upper timer counter have reached desired value
	BRLT	FINAL_STOP		; otherwise recheck the lower bytes
	RJMP	COMEBACK_DOS	; jumps to COMEBACK_DOS
	
FINAL_STOP:
	LDS		r29, TCNT1H		; load upper bytes of timer counter to r29
	LDS		r28, TCNT1L 	; load lower bytes of timer counter to r28
	CPI		r28, 0x8C		; check to see if lower 8 bits of timer counter are 0x08
	BRSH	SHOWDOWN_2		; keep checking lower bytes
	RJMP	FINAL_STOP		; jummps to FINAL_STOP
