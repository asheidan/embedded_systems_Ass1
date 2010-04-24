#ifndef _UART_H_
#define _UART_H_

#define	SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define	CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))


void InitUART( unsigned int baud );

unsigned char ReceiveByte( void );

void TransmitByte( unsigned char data );
void TransmitString( char* data );


#endif