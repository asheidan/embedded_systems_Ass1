#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "control.h"
#include "collision.h"
#include "uart.h"
#include "leds.h"

#define	SYSTEM_ADDRESS	'c'

volatile unsigned char sensor_cache = 0;

int main() {
	/******************************************************
	 *	Setting up device
	 ******************************************************/
	//DDRD = 0xFF; // Set Datadirection to output
	// UART
	InitUART(51);			// 1200 Baud, 1 Mhz
	
	InitControl();
	InitCollision();
	
	// Sleep
	set_sleep_mode(SLEEP_MODE_IDLE);
	// TODO: Disable Analog Comparator
	
	TransmitString("Hello World!!!\n\r");

	sei();
	/******************************************************
	 *	Main loop
	 ******************************************************/
	for(;;) { 
		sleep_enable();
		sleep_cpu();
  	} 
}

/******************************************************
 *	Interrupt handlers
 ******************************************************/

// Collision
ISR(PCINT_vect) {
	unsigned char sensors = COLLISION_DATA;
	motors_stop();
	if(sensors != sensor_cache) {
		sensor_cache = (~sensors & COLLISION_PINS);
		// TODO: transmit to remote
	}
#ifdef __DEBUG__
	TransmitString("\n\rCollision: ");
	TransmitByte(sensor_cache + '0');
	TransmitString("\n\r");
#endif
}

// USART, Recieve complete
ISR(USART_RX_vect) {
	unsigned char data, checksum;
	data = ReceiveByte();
	if(data == SYSTEM_ADDRESS) {
		TransmitString("HELO\n\r");
		data = ReceiveByte();
		checksum = ReceiveByte();
#ifndef __DEBUG__
		if( checksum == (data ^ SYSTEM_ADDRESS)) {
#endif
			ControlMotors(data);
#ifndef __DEBUG__
		}
#else
		TransmitString("\n\rData:     '");
		TransmitByte(data);
		TransmitString("'\n\rChecksum: '");
		TransmitByte(checksum);
		TransmitString("'\n\r");
#endif
	}
}