#include <avr/io.h>
#include "leds.h"

void delay() {
	unsigned char a,b;
	
	for(a = 0; a < 5; a++) {
		for(b = 0; b < 255; b++);
	}
}

void LED_On(int i) {
	PORTD = _BV(i);
	// delay();
}
