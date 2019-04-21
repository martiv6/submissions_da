/*
 * DA4B_T2.c
 *
 * Created: 4/19/2019 5:12:26 PM
 * Author : victor
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int motor_status = 0;

int main(void)
{
	
	DDRB = 0b11111111;										 //	port b as an output
	DDRD = 0b11111111;										 //	port d as an output
	TCCR0A= 0b10000011;										 // set fast PWM and clears OCR0A on MATCH
	TCCR0B= 0b0101;											 // set prescaler to 1024
	ICR1=4999;												 // fast Pulse Width Modulation 
	ADMUX = 0b1100000;										 // enables PC0 as the pin for ADC
	ADCSRA = 0b10100110;									 // This register is responsible for enabling ADC

	while (1)
	{ 
		//start conversion
		ADCSRA |= ( 0b0001 << ADSC);
		
		while((ADCSRA & (1 << ADIF))== 0b0);
		motor_status = ADCH;								 // the adc value that is inputed
		
		if(motor_status == 0)								 // if the potentiometer is at the lowest setting 
		{
			OCR1A = 0b0000;									 // turn to zero degree position 
			_delay_ms(500);									 // for debouncing 
		}
		
		if(motor_status == 0b11111111)						 // if the potentiometer is at the highest setting 
		{
			
			OCR1A = 0b1000011100;							 // turn to 180 degree position 
			_delay_ms(500);									 // for debouncing
		}
	}
}

