#include <avr/io.h>
#include "uart.h"

void delay() {
	unsigned char a,b;
	
	for(a = 0; a < 5; a++) {
		for(b = 0; b < 255; b++);
	}
}

void LED_On(int i) {
	PORTD = _BV(i);
	delay();
}

int main() {
	// int i = 1;
	DDRD = 0xFF; // Set Datadirection to output
	InitUART(51);			// 1200 Baud, 1 Mhz
	unsigned char	ch;
	char *msg = "Hello World!!!\n\r";
	TransmitString(msg);
	
	for(;;) { 
		LED_On(2);
		ch = ReceiveByte();
		LED_On(3);
		// PORTD = (ch & 0x0F) * 4;
		LED_On(4);
		if(ch == '\r') {
			TransmitString("\n\r");
		}
		else {
			if(ch >= 'a' && ch <= 'z') {
				ch += 'A' - 'a';
			}
			TransmitByte(ch);
		}
  	} 
	
	// for(;;) {
	// 	for(; i < 5; i++) {
	// 		LED_On(i);
	// 	}
	// 	for(; i > 1; i--) {
	// 		LED_On(i);
	// 	}
	// }
}