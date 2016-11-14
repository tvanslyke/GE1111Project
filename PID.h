/*
 * PID.h
 *
 *  Created on: Nov 10, 2016
 *      Author: tim
 *
 *      Somewhat clumsy class for PID control.
 */

#ifndef PID_H_
#define PID_H_
#include "stdint.h"
#include "limits.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/HardwareSerial.h"
class PID {
private:
	// setpoint value
	int16_t sp;
	// value of proportional, derivative, and integral terms
	int16_t p, d, i;
	// value of the input control (location where output is written to as well)
	int16_t * value;
	// bitshift factor applied to output so as to avoid floating arrithmetic on
	// the PID constants
	uint8_t shift;
public:
	// PID constants.  should be set such that '(PID_CONSTANT) >> shift' would produce
	// the desired decimal value for each.
	int16_t P, I, D;
	PID(int16_t, int16_t *, uint8_t);
	PID(int16_t,int16_t, int16_t, int16_t, int16_t *, uint8_t);
	virtual ~PID();

	// updates the 'value' pointer to the PID-control output calculation
	void Update();
};

#endif /* PID_H_ */
