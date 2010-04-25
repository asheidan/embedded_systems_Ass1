#ifndef _CONTROL_H_
#define _CONTROL_H_

#define	motors_stop()		ControlMotors(0x00)
#define	motors_forward()	ControlMotors(0b0000101)
#define	motors_reverse()	ControlMotors(0b0001010)


void InitControl();

void ControlMotors(unsigned char control);

#endif