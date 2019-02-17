;
; AssemblerApplication1.asm
;
; Created: 2/11/2019 6:46:31 PM
; Author : victor
;


CLR R0				  //clears value in r0
CLR R1				  //clears value in r1
LDI R17, 0			  //used if there is carry
LDI R18, 0			  //where the MSB will be stored
LDI R19, 0			  //where the middle values will be stored if more than 8 bits	
LDI R20, 0			  //where the LSB will be stored 		
LDI R22, 0x45		  //the value of the 8 bit multiplier 
LDI R24, 0x1D		  //the first 8 bits of the 16 bit multiplicand	
LDI R25, 0x35		  //the last 8 bits of the 16 bit muliplicand

MUL R22, R25		  //multiplies the 0x45 by 0x1D 
ADD R18, R0			  //adds r0 to r18
ADC R19, R1			  //adds r1 to r17 with carry if needed
ADC R20, R17		  //adds r17 to r20 with carry if needed

MUL R22, R24		  //multiples the multipicand with whats in r24
ADD R19, R0			  //adds r0 to r 19
ADD R20, R1			  //adds r1 to r20 

BREAK
