#include <avr/io.h>

#include "timer.h"
#include "bits.h"

void InitTimer() {
	SETBIT(TIMSK,OCIE1A);	//enable timer 1 compare interrupt
	TCCR1B |= 10;			//clear counter on compare match and prescaler 8
	TCCR1A |= 0x40;			// toggle OC1 output
	OCR1AH = 0x3d;			// 125 msec, 1 MHz
	OCR1AL = 0x09;
}

