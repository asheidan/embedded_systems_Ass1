//connect 4 LEDs between PD2,PD3,PD4,PD5 and GND
//with anode to pin and cathode to GND

//connect to buttons between PB0, PB1 and GND

//connect PD0 ( RXD) to STK500 RXD 
//and PD1 (TXD) to STK500 TXD	( see picture )

//CPU freq 1 MHz

#include <avr/io.h> 
#define	SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define	CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))


/* initialize UART */
void InitUART( unsigned int baud )
	{
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;				//set the baud rate 
	UCSRB = _BV(RXEN) | _BV(TXEN);	//enable UART receiver and transmitter 
	}

/* Read and write functions */
unsigned char ReceiveByte( void )
	{
	loop_until_bit_is_set(UCSRA,RXC);		// wait for incomming data 
	return UDR;							// return the data 
	}

void TransmitByte( unsigned char data )
	{
	loop_until_bit_is_set(UCSRA,UDRE);	// wait for empty transmit buffer 
	UDR = data; 						// start transmittion 
	}

int main()  { 
 	DDRD = 0xFF;			// output
	DDRB = 0;				// input
	SETBIT(PORTB,PB0);		// enable pull-up
	SETBIT(PORTB,PB1);		// enable pull-up
	InitUART(51);			// 1200 Baud, 1 Mhz
	unsigned char	ch;

 	for(;;)  { 
		ch = ReceiveByte();
		PORTD = (ch & 0x0F) * 4;
		if(bit_is_clear(PINB,PB0))	TransmitByte(ch);
  	} 
 } 
