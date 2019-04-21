/*
 * DA4B_T1.c
 *
 * Created: 4/18/2019 1:30:14 PM
 * Author : victor
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void adc_initializer(void);												// void function we will use for ADC
void slow_the_freak_up(void);											// does this to begin slowing down the motor
void whats_the_speed(void);												// checks what is the speed with the potentiometer
volatile unsigned int speed_motor;										// variable used to control the speed of the motor
volatile int stop_motor = 0;											// if 1, the motor will stop

int main(void)
{
	DDRB = 0b1111;														//Enable output on all of the B pins
	PORTB = 0b0000;														// makes the fisrt value 0
	adc_initializer();													// initialize ADC
	TCCR1B = 0b11010;													// set CTC mode and 1024 prescaler
	ICR1 = 62258;														// fast Pulse Width Modulation 
	
	while(1)		
	{
		
		whats_the_speed();												// checks what is the speed with the potentiometer 
		OCR1A = speed_motor;											// set OCR1A to the determined speed
		TCNT1 = 0x00;													// reset the clock
	
		if(stop_motor == 0)												// leads to the motor stopping 
		{
			 slow_the_freak_up();										// calls the function to slow down
		}
	}
}

void adc_initializer(void) 												//initialize ADC
{
	ADMUX = (0<<REFS1)|(0<<REFS0);										// ADC Enable
	ADCSRA = (1<<ADEN)| (1<<ADSC)| (1<<ADATE)| (0<<ADIF)|				// ADC Start Conversion
	(0<<ADIE)| (1<<ADPS2)|(1<<ADPS1)| (1<<ADPS0);						// ADC Auto Trigger Enable
																		// ADC Interrupt Flag
																		// ADC Interrupt Enable
																		// ADC Prescaler Select Bits
																		// ADC Prescaler select bits
																		// ADC input
																		// Timer/Counter1 Interrupt Mask Register
}

void slow_the_freak_up(void)
{
	// does this to begin slowing down the motor
	while((TIFR1 & 0x2) != 0b0010);
	PORTB = 0x09;
	TIFR1 |= (1<<OCF1A);
	while((TIFR1 & 0x2) != 0b0010);
	PORTB = 0x03;
	TIFR1 |= (1<<OCF1A);
	while((TIFR1 & 0x2) != 0b0010);
	PORTB = 0X06;
	TIFR1 |= (1<<OCF1A);
	while((TIFR1 & 0x2) != 0b0010);
	PORTB = 0X0C;
	TIFR1 |= (1<<OCF1A);
}

void whats_the_speed(void)
{
	// reads at what speeds the motor is 
	while((ADCSRA&(1<<ADIF))==0);
	if (ADC >= 820){ stop_motor = 1;}
	if ((ADC < 820) && (ADC >= 617)) { stop_motor = 0; speed_motor = 0x1869;}
	if ((ADC < 617) && (ADC >= 414)) { stop_motor = 0; speed_motor = 0x124F;}
	if ((ADC < 414) && (ADC >= 211)) { stop_motor = 0; speed_motor = 0x0C34;}
	if ((ADC < 211) && (ADC >= 000)) { stop_motor = 0; speed_motor = 0x061A;}
}