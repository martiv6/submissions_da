/*
 * DA2C_T1_2.c
 *
 * Created: 3/22/2019 2:17:32 PM
 * Author : victor
 */ 

#include <avr/io.h>
#define F_CPU   16000000UL
#include <util/delay.h>


int main(void)
{
	uint8_t timerOverflowCount=0;
	DDRB = 0b0100;					// set PB2 as output when pressed
	PORTB = (0b0001<<0b0101);		// turn off PB5 LED
	DDRC = (0b0000<<0b0001);		// reads data entered
	PORTC = (0b0001<<0b0001);		// will cause it to light up and display
	TCNT0 = 0b0000;					//sets register to 0
	TCCR0B |= (0b0001<< CS02) | (0b0001 << CS00); // makes prescalar to 1024 
	
	while (1)
	{
	
		if(!(PINC & (0b0001<<PINC2)))	//to see if the switch is pressed
		{
			timerOverflowCount=0;	// if there is no input keep led off
			TCNT0= 0b0000;			// resets timer
			PORTB=0b0000;			//turns on led
		}
			
		while ((TIFR0 & 0x01) == 0);
		
			TIFR0=0x01;							// reset the overflow flag
			timerOverflowCount++;				// counts every time the timer overflows
			
		if(timerOverflowCount==76)
		{
			PORTB = 0b0100;	// toggle the led
		}
		TCNT0=0b0000;
	}
	return 0;
}

