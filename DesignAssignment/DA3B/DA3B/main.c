/*
 * DA3A.c
 *
 * Created: 3/27/2019 2:47:19 PM
 * Author : martiv6
 */ 

#define F_CPU 16000000UL 
#define BAUD 9600 
#define MYUBRR F_CPU/16/BAUD-1 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

void read_adc(void);													// where the ADC is read
void adc_initializer(void);												// where ADC initializes
void USART_init( unsigned int ubrr );									// where USART initializes
void USART_tx_string(char *data);										// where it print string USART
volatile unsigned int room_temp;										// where we store the temp of the ADC
char outs[35];															// room we have to print

int main(void) 
{
	adc_initializer();													// Initialize the ADC (Analog / Digital Converter)
	USART_init(MYUBRR);													// Initialize the USART (RS232 interface)
	USART_tx_string("Connected!\r\n");									// shows theres a connection with USART
	_delay_ms(125);														// waits
	sei();																// enable global interrupts
	while(1)															// waits for interrupt
	{
	}
}

void adc_initializer(void)
{
	ADMUX = (0<<REFS1)|													// Reference Selection Bits
	(1<<REFS0)|															// AVCC- external cap at AREF
	(0<<ADLAR)|															// ADC Left Adjust Result
	(1<<MUX2)|															// Analog Channel Selection Bits
	(0<<MUX1)|															// PC5 is where its monitoring 
	(1<<MUX0);
	ADCSRA = (1<<ADEN)|													// ADC enabled
	(0<<ADSC)|															// ADC start conversion
	(0<<ADATE)|															// ADC auto trigger enable
	(0<<ADIF)|															// ADC interrupt flag
	(0<<ADIE)|															// ADC interrupt enable
	(1<<ADPS2)|															// ADC prescaler select bits
	(0<<ADPS1)|															// ADC prescaler select bits
	(1<<ADPS0);															// ADC input
																		// Timer/Counter1 Interrupt Mask Register
	TIMSK1 |= (1<<TOIE1);												// enable overflow interrupt
	TCCR1B |= (1<<CS12)|(1<<CS10);										// clock
	TCNT1 = 49911;														//((16MHz/1024)*1)-1 = 15624
}

void read_adc(void)														// initialize to begin to read from the sensor 
 {
	unsigned char i =4;													// to keep track of input 
	room_temp = 0;														
	while (i--)
	 {
		ADCSRA |= (1<<ADSC);											// used to start convo with chips
		while(ADCSRA & (1<<ADSC));
		room_temp+= ADC;
		_delay_ms(50);
	}
	room_temp = room_temp/8 ;											// gets correct value displayed 
}

/* INIT USART (RS-232) */
void USART_init( unsigned int ubrr )
 {
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);												// Enable receiver, transmitter & RX interrupt
	UCSR0C = (3 << UCSZ00);												// asynchronous 8 N 1
}

void USART_tx_string( char *data )										// used to print on to the screen
{			
	while ((*data != '\0')) 
	{
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}

ISR(TIMER1_OVF_vect)													// timer overflow interrupt to delay for 1 second
{
	read_adc();															// read ADC
	snprintf(outs,sizeof(outs),"%3d F \r\n", room_temp);				// prints it
	USART_tx_string(outs);												// prints spaces
	TCNT1 = 49911;														// reset tcnt value for delay
}