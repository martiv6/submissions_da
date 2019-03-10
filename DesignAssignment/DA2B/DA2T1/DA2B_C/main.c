/*
 * DA2B.c
 *
 * Created: 3/9/2019 9:32:56 AM
 * Author : victor
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 1<<2;		 // PB2 as an output
	PORTB = 1<<2;		 // keeps led low
	PORTD = 1 << 2;		 // pull-up activated
	DDRB |= 1<<5;		 // turns off led thats always one
	PORTB |= 1<<5;		 // set it to low
	EIMSK = (1 << INT0); // enable external interrupt
	sei();				 // enables the interrupt
	
	while (1);			 // waits until there is an interrupt 
}

ISR(INT0_vect)
{
	PORTB ^= ( 1 << 2);	// lights up the led 
	_delay_ms(1250);	// delays the led 
	PORTB ^= ( 1 << 2); // lights up the led 

}
