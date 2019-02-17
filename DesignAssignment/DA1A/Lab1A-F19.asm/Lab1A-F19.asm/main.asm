;
; Lab1A-F19.asm.asm
;
; Created: 2/9/2019 12:45:56 PM
; Student Name : Victor Martinez
; Student # : 5003131674
; Student Email : martiv6@unlv.nevada.edu
; Primary Github address:https://github.com/martiv6/submissions_da

LDI R17, 0			  //used if there is carry
LDI R18, 0			  //where the MSB will be stored
LDI R19, 0			  //where the middle values will be stored if more than 8 bits	
LDI R20, 0			  //where the LSB will be stored 		
LDI R22, 0x45		  // the value of the 8 bit multiplier 
LDI R24, 0x1D		  // the first 8 bits of the 16 bit multiplicand	
LDI R25, 0x35		  // the last 8 bits of the 16 bit muliplicand


					  // this is were it will loop adding the values until R22 is equal to 0 
pizza: ADC R20, R25   // puts the LSB in R20 
	   ADC R19, R24   // puts the next values in R19
       ADC R18, R17   // adds zero and any carry from the additions
       DEC R22        // subtracts one from R22 until it hits 0
       BRNE pizza     // ends loop when equal to zero
end:
BREAK				  // if loops doesnt stop this will make sure it does

