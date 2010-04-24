//connect 4 LEDs between PD2,PD3,PD4,PD5 and GND
//with anode to pin and cathode to GND

//connect to buttons between PB0, PB1 and GND

//connect PD0 ( RXD) to STK500 RXD 
//and PD1 (TXD) to STK500 TXD	( see picture )

//CPU freq 1 MHz

#include <avr/io.h> 
#include <avr/interrupt.h>

#include "control.h"
#include "uart.h"
#include "leds.h"
#include "bits.h"

//0x55FF
#define	UART_SYNC_DATA	"\085\255"

/* initialize UART */
void InitUART( unsigned int baud ) {
	// DDRD = 0xFF; // Set Datadirection to output
	// InitUART(51);			// 1200 Baud, 1 Mhz
	
	DDRD = 0xFF;			// output
 	
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;				//set the baud rate 
	UCSRB = _BV(RXEN) | _BV(TXEN);	//enable UART receiver and transmitter 
	
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<USBS)|(3<<UCSZ0);
	
	/* Enagle RC_Int */
	UCSRB |= (1<<RXCIE);
	
}

/* Read and write functions */
unsigned char ReceiveByte( void ) {
	loop_until_bit_is_set(UCSRA,RXC);		// wait for incomming data 
	return UDR;							// return the data 
}

void TransmitByte( unsigned char data ) {
	loop_until_bit_is_set(UCSRA,UDRE);	// wait for empty transmit buffer 
	UDR = data; 						// start transmittion 
}

void TransmitString( char* data ) {
	char *p;
	for(p = data; *p != 0; p++) {
		TransmitByte(*p);
	}
}
