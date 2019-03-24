//*
 * DA2C_T1.c
 *
 * Created: 3/13/2019 11:35:50 AM
 * Author : victor
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
	uint8_t timerOverflowCount=0;			//counts how many overflows occur
	
	DDRB = 0b0100;							// makes pd2 an output
	TCCR0A = 0b0000;						// normal Operation
	TCNT0= 0b0000;							// start the timer
	TCCR0B |= (0b0001 << CS02) | (0b0001 << CS00);	// set prescaler to 1024 and start the timer
	

	while (1)
	{
											// wait for the overflow event
		while ((TIFR0 & 0x01) == 0);
		TCNT0=0x00;							// resets the timer to zero
		TIFR0=0x01;							// reset the overflow flag
		timerOverflowCount++;				// counts every time the timer overflows
		
		if (timerOverflowCount==18)			// gets delay of 290ms
		{
			PORTB= ~(1 << PORTB2);				//will turn on led 
		}
		if(timerOverflowCount== 44)			// turns off led for 435 ms
		{
	
		PORTB = (1 << PORTB2);				//turns off the led we want
		timerOverflowCount=0;
		}
	}
}	