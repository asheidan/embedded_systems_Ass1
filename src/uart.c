
//CPU freq 1 MHz

#include <avr/io.h> 

#include "control.h"
#include "uart.h"
#include "bits.h"
#include "transceiver.h"

//0x55FF
#define	UART_SYNC_DATA	"U\xFF"

/* initialize UART */
void InitUART( unsigned int baud ) {
	// DDRD = 0xFF; // Set Datadirection to output
	// InitUART(51);			// 1200 Baud, 1 Mhz
	
	// DDRD = 0xFF;			// output
 	
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;				//set the baud rate 
	UCSRB = _BV(RXEN) | _BV(TXEN);	//enable UART receiver and transmitter 
	
	/* Set frame format: 8data, 2stop bit */
	// UCSRC = (1<<USBS)|(3<<UCSZ0);
	UCSRC = (1<<USBS)|(1<<UCSZ0)|(1<<UCSZ1);
	
	/* Enagle RC_Int */
	UCSRB |= (1<<RXCIE);
	
	InitTransceiver();
	
}

/* Read and write functions */
unsigned char ReceiveByte( void ) {
	loop_until_bit_is_set(UCSRA,RXC);		// wait for incomming data
	unsigned char t = UDR;
	// TransmitByte(t);
		return t; //UDR;							// return the data 
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

void RadioTransmit( unsigned char data ) {
	SetTransmitMode();
	TransmitString(UART_SYNC_DATA);
	TransmitByte(UART_REMOTE_ADDRESS);
	TransmitByte(data);
	TransmitByte(data ^ UART_REMOTE_ADDRESS);
	TransmitByte(0xFF);
	TransmitByte(0xFF);
	SetRecieveMode();
}
/*
int main() {
	InitUART(25);
	for(;;) {
		TransmitByte(0x55);
	}
}
*/