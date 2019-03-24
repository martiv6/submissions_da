/*
 * DA2C_T3_2.c
 *
 * Created: 3/22/2019 2:38:57 PM
 * Author : victo
 */ 


#include <avr/io.h>
#define F_CPU   16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{

	DDRB = 0b0100;					// set PB2 as output when pressed
	PORTB = (0b0001<<0b0101);		// turn off PB5 LED
	DDRC = (0b0000<<0b0001);		// reads data entered
	PORTC = (0b0001<<0b0001);		// will cause it to light up and display
	TCNT0 = 0b0000;					//sets register to 0
	TCCR0A |= (0b0001<< WGM01);		//ctc mode enable 
	TCCR0B |= (0b0001<< CS02) | (0b0001 << CS00); // makes prescalar to 1024
	TIMSK0 |= (0b0001<< OCIE0A);				//enables campare match
	sei ();
	
	while (1)
	{
		
	}
	
}

ISR(TIMER0_COMPA_vect)
{
	uint8_t timerOverflowCount=0;
	while ((TIFR0 & 0x01) == 0);
	TCNT0=0x00;							// resets the timer to zero
	TIFR0=0x01;							// reset the overflow flag
	timerOverflowCount++;				// counts every time the timer overflows
	
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





