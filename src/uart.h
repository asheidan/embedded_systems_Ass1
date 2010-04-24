#ifndef _UART_H_
#define _UART_H_

void InitUART( unsigned int baud );

unsigned char ReceiveByte( void );

void TransmitByte( unsigned char data );
void TransmitString( char* data );


#endif