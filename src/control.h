#ifndef _CONTROL_H_
#define _CONTROL_H_

#define motors_stop()	ControlMotors(0x00)

void InitControl();

void ControlMotors(unsigned char control);

#endif