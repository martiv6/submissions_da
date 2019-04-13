/*
 * DA4A.c
 *
 * Created: 4/10/2019 10:48:31 AM
 * Author : victor
 */ 

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void adc_initializer(void);												// void function we will use for ADC
int motor_control;														// to be able to control the motor with the potentiometer
int	motor_status = 0;													// to toggle the motor with the switch will be off at first

int main()
{
	DDRD = 0b01000000;													// sets port d as output
	DDRC = 0b0010;														// sets port c as output
	PORTC |= (0b0001<<0b0001);											// enable pull-up pin
	PCICR = 0b0010;														// enable PCIE1 to make PCMSK1 work
	PCMSK1 = 0b0010;													// enable pin changes
	TCCR0A= 0b10000011;													// set fast PWM and clears OCR0A on MATCH
	TCCR0B= 0b0101;														// set prescaler to 1024
	sei();																// enable interrupts
	adc_initializer();													// initializes ADC
	
	while (1)
	{																	// waits for an interrupt
	}
}

ISR(PCINT1_vect)
{
	if(!(PINC & (1<<PINC1)))											// when the button is pressed it goes into this loop to determine if will be on or off
	{
		if(motor_status == 0)											// when the button is pressed the motor will stop
		{
			OCR0A = 0;													// stops the motor
			_delay_ms(1500);											// meant for debouncing to make sure its a clean reading
		}
		if (motor_status == 1)											// when the button is pressed again it will stay on
		{
			while((ADCSRA&(1<<ADIF))==0);								// wait for conversion
			motor_control = ADC;										// puts ADC value into motor control so we can then keep it on
			OCR0A = motor_control;										// Output to converted value to 0CR0A and makes the motor run
			_delay_ms(1500);											// meant for debouncing to make sure its a clean reading 
		}
		motor_status ^= 1;												// update state of motor to on
	}
}

void adc_initializer(void) 												//initialize ADC
{
	ADMUX = (0<<REFS1);													// ADC ENable
	ADCSRA = (1<<ADEN)| (1<<ADSC)| (1<<ADATE)| (0<<ADIF)|				// ADC Start Conversion
	(0<<ADIE)| (1<<ADPS2)|(1<<ADPS1)| (1<<ADPS0);						// ADC Auto Trigger Enable
																		// ADC Interrupt Flag
																		// ADC Interrupt Enable
																		// ADC Prescaler Select Bits
																		// ADC Prescaler select bits
																		// ADC input
																		// Timer/Counter1 Interrupt Mask Register
}
