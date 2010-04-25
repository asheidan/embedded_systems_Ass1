#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "bits.h"
#include "collision.h"
#include "control.h"
#include "timer.h"
#include "uart.h"


int main() {
	/******************************************************
	 *	Setting up device
	 ******************************************************/
	// DDRD = 0xFF; // Set Datadirection to output
	// UART
	InitUART(51);			// 1200 Baud, 1 Mhz
	
	InitControl();
	InitCollision();
	InitTimer();
	
	// Sleep
	set_sleep_mode(SLEEP_MODE_IDLE);
	// FIXED: Disable Analog Comparator
	// Disable compare interrupt
	CLEARBIT(ACSR,ACIE);
	// Disable compare
	SETBIT(ACSR,ACD);
#ifdef __DEBUG__
	TransmitString("Hello World!!!\n\r");
#endif

	sei();
	motors_forward();
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
	unsigned char sensors = (~COLLISION_DATA & COLLISION_PINS);
	motors_stop();
	if(sensors > 0) {
		// TODO: transmit to remote
		RadioTransmit(sensors);
#ifdef __DEBUG__
		TransmitString("\n\rCollision: ");
		TransmitByte(sensors + '0');
		TransmitString("\n\r");
#endif
	}
}

// Timer ~8Hz
ISR(TIMER1_COMPA_vect) {
	// TODO: IR sensor communication
	sleep_disable();
}


// USART, Recieve complete
ISR(USART_RX_vect) {
	unsigned char data, checksum;
	data = ReceiveByte();
	if(data == UART_SYSTEM_ADDRESS) {
#ifdef __DEBUG__
		TransmitString("HELO\n\r");
#endif
		data = ReceiveByte();
		checksum = ReceiveByte();
#ifndef __DEBUG__
		if( checksum == (data ^ UART_SYSTEM_ADDRESS)) {
#endif
			ControlMotors(data);
#ifndef __DEBUG__
		}
#else
		TransmitString("Data:     '");
		TransmitByte(data);
		TransmitString("'\n\rChecksum: '");
		TransmitByte(checksum);
		TransmitString("'\n\r");
#endif
	}
}