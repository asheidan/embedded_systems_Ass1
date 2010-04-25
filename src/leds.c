#include <avr/io.h>
#include "delay.h"
#include "leds.h"

void LED_On(int i) {
	PORTD = _BV(i);
	delay();
}

int main() {
	DDRD = 0xFF;
	unsigned char i;
	
	for(i = 0;;i++) {
		PORTD = i;
		delay();
	}
}
