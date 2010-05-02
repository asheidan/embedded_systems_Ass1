#include "transceiver.h"

#include <avr/io.h>

#include "delay.h"
#include "bits.h"

void InitTransceiver() {
	DDRA |= 0b00000001;
	SetRecieveMode();
}

void SetTransmitMode() {
	PORTA |= 0b00000001;
	_delay_ms(1);
	// SETBIT(UCSRA,TXC);
	// SETBIT(UCSRA,RXC);
}

void SetRecieveMode() {
	PORTA &= 0b11111110;
	_delay_ms(3);
	// SETBIT(UCSRA,TXC);
	// SETBIT(UCSRA,RXC);
}
