/*
 * DA2C_T2.c
 *
 * Created: 3/19/2019 1:45:49 PM
 * Author : victor
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	
	
	DDRB |= (0b0001 << DDB2);						//PB1 as output
	TIMSK0 =0b0001;									// enables timer0 interrupt
	TCNT0 = 0b0000;									// initial value
	sei();
												//enable interrupts
	TCCR0B |= (0b0001 << CS02) | (0b0001 << CS00);
												// set prescaler to 1024 and start the timer
	while (1)
	{
												//main loop
	}
}
uint8_t timerOverflowCount=0;
ISR (TIMER0_OVF_vect)							// timer0 overflow interrupt
{
	
	
		TCNT0=0x00;							// resets the timer to zero
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