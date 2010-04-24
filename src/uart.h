#ifndef _UART_H_
#define _UART_H_

#define	UART_SYSTEM_ADDRESS	'c'

void InitUART( unsigned int baud );

unsigned char ReceiveByte( void );

void TransmitByte( unsigned char data );
void TransmitString( char* data );

void RadioTransmit( unsigned char data );
#endif