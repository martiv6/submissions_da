;
; DA1B.asm
;
; Created: 2/20/2019 11:46:41 AM
; Author : victor
;
 
.equ STARTADDS = 0x0200   ;where the memory address will start
.equ numvalues = 99	      ;the number of values we need 
.equ minvalue = 21		  ;the min value we start with 
.equ dividend =3 		  ;the value we are dividing by
.equ maxvalue = 255		  ;the max value that can be ran 
.org 0
 
CLR R0				      ;clears value in R0
CLR R16					  ;clears value in R16
CLR R17					  ;clears value in R17
CLR R18					  ;clears value in R18
CLR R19					  ;clears value in R19
CLR R24					  ;clears value in R24

LDI R22, numvalues		  ;loads the number of values in to R22
LDI R23, minvalue		  ;loads min value will be in R23 greater than 10
LDI R25, maxvalue		  ;loads max value will be in R25 less than 255

LDI XL, low(STARTADDS)    ;sets the lower bits of register X
LDI XH, high(STARTADDS)	  ;sets the higher bits of register X

LDI YL, low(0x400)	      ;sets the lower bits of register Y as well is where we will store the values that are divisible by 3
LDI YH, high(0x400)       ;sets the higher bits of register Y as well is where we will store the values that are divisible by 3

LDI ZL, low(0x600)	      ;sets the lower bits of register Z as well is where we will store the values that are NOT divisible by 3
LDI ZH, high(0x600)		  ;sets the higher bits of register Z as well is where we will store the values that are NOT divisible by 3

BEGIN:
MOV R24, R23			  ;places min value into R24 to BEGIN testing values
ST X+, R23				  ;also places min value in X register 
CP R25, R24				  ;makes sure the value isnt over 255
BRGE ITSOVER			  ;if value over 255 it is not placed in either register 
RJMP BOUNCER			  ;sent over to check if able to be divided by 3

BOUNCER:				
SUBI R24, dividend		  ;will substract by 3 
BRLT KICKOUT			  ;if less then zero its KICKOUT
BREQ YOUGOOD	          ;if its equal to zero its good to be divided	
RJMP BOUNCER		      ;	checks the next value

YOUGOOD:				  ;adds the value to R16 and R17 that are divisble by 3
ST Y+, R23				  ;puts it to the high bits of Y
ADD R16, R23			  ;adds value of R23 to R16 
ADC R17, R0				  ;puts any overflow from R0 
RJMP ITSOVER              ;goes to ITOVER

KICKOUT:				  ;adds the value to R18 and R19 that are NOT divisble by 3
ST Z+, R23				  ;it puts the value that cant be divided into the Z register
ADD R18, R23			  ;adds value of R23 to R18 	
ADC R19, R0				  ;puts any overflow from R0
RJMP ITSOVER			  ;jumps to ITSOVER

ITSOVER:
INC R23					  ;adds one to value in R23 to goto the next value 
DEC R22					  ;substracts one to R22 bc we did the first value of 99
BRNE BEGIN				  ;goes to the BEGINning
BREAK

 
 
