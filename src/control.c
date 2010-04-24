#include <avr/io.h>

#include "control.h"

#define MOTOR_PINS 0b00111100

void InitControl() {
	DDRD |= MOTOR_PINS;
}

void ControlMotors(unsigned char control) {
	unsigned char signals = (control << 2);
	PORTD |= signals & MOTOR_PINS;
	PORTD &= signals | ~MOTOR_PINS;
}
