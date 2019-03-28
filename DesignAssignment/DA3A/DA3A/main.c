/*
 * DA3A.c
 *
 * Created: 3/25/2019 6:14:06 PM
 * Author : martiv6
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define BAUDRATE 9600
#define BAUD_PRESCALLER ( (F_CPU /BAUDRATE/16UL) - 1)

// Function that need to be declared 


char luke[] = "	 ";									// declares the amount of spaces between words and numbers
char outs[30];										// the amount of spaces thats displayed 
char str[] = "YOUR FATHER";							// declare the string and hold value for 'your father'
float pizza=3.14666;								// declare the floating point and assign the value
int darth;											// the variable that holds the random integer
volatile int counter;								// counter to use when using timer0 and calculate when to make 1 second delay 
void USART_init( unsigned int ubrr );				// calls integer
void USART_tx_string( char *data );					// calls string

int main(void)
{
	counter=0;										// sets counter to zero to begin counting 
	TIMSK0 |= (1<<TOIE0);							// sets timer0
	sei();											
	TCCR0A = 0b0000;								// sets to normal mode
	TCCR0B |= (0b0001<<CS02)|(0b0001<<CS00);		// sets prescaler to 1024
	USART_init(BAUD_PRESCALLER);					// Initialize the USART
	USART_tx_string("Connected!\r\n");				// shows that it is ready to display
	USART_tx_string(luke);							// puts space to seprate 
	while(1);
}

ISR(TIMER0_OVF_vect)
{
	while(counter < 61)								// counts and keeps counting until gets over amount to then display 
		if((TIFR0 & 0b0001)==1)
		{
			TIFR0=0b0001;
			counter++;
		}
		
if (counter>60)
{
	USART_tx_string(str);								// displays the string value
	USART_tx_string(luke);								// puts space between number and words 
	
	darth= rand();										// gets value for random number 
	snprintf(outs, sizeof(outs), "%3d\r\n", darth);		// prints out the random number 
	USART_tx_string(outs);								// makes room for things to be printed 
	USART_tx_string(luke);								// displays the space between values
	
	pizza= 3.14666;										// value of float
	dtostrf(pizza, 1, 4, outs);							// prints out 1 number before decimal and prints 4 after the decimal  
	USART_tx_string(outs);								// makes room for things to be printed 
	USART_tx_string(luke);								// displays the space between values
	counter=0;											// restarts counter 
}
	
}

/* INIT USART (RS-232)  */
void USART_init( unsigned int ubrr )
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Enable UART receiver and transmitter */
	UCSR0B = ((1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0));
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); //asynchronous 8 N 1
}

/* SEND A STRING TO THE RS-232 */
void USART_tx_string( char *data )
{
	while ((*data != '\0'))
	{
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}