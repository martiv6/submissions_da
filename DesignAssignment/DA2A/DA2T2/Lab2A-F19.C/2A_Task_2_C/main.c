/*
 * 2A_Task_2_C.c
 *
 * Created: 3/1/2019 6:16:17 PM
 * Author : victor
 */ 

#include <avr/io.h>
#define F_CPU   16000000UL
#include <util/delay.h>


int main(void)
{
	DDRB = 0b0100;					// set PB2 as output when pressed
	PORTB = (0b0001<<0b0101);		// turn off PB5 LED
	DDRC = (0b0000<<0b0001);		// reads data entered
	PORTC = (0b0001<<0b0001);		// will cause it to light up and display

	while (1)
	{
		if(PINC & (PINC1<<PINC1))	//to see if the switch is pressed
		{
			PORTB = (PORTB1<<PORTB2);	// if there is no input keep led off
			
		}
		
		else 
		{
			PORTB &= ~(PORTB1<<PORTB2);	// toggle the led
			_delay_ms(1250);	// keep the light on for 1.25 SECONDS
		}
		
	}
	return 0;
}


