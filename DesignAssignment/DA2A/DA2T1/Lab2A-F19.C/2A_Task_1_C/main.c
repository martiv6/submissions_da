/*
 * 2A_Task_1_C.c
 *
 * Created: 3/1/2019 12:09:53 PM
 * Author : victor
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
    DDRB = 0b0100;			//makes pd2 an output 
	
    while (1) 
    {
		PORTB = (1 << PORTB2);	//turns on the led we want
		_delay_ms(435);			//time the led will be off to get the 60% DC with the period of 0.725 
		PORTB= ~(1 << PORTB2);	//will turn on led 
		_delay_ms(290);			//the time the led will be on to get the 40% DC with the period of 0.725 
    }
	return 0; 
}


