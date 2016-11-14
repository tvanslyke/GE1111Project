/*
 * PID.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: tim
 */

#include "PID.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/HardwareSerial.cpp"


// Constructors
PID::PID(int16_t setpoint, int16_t * val, uint8_t shft) {
	// TODO Auto-generated constructor stub
	sp = setpoint;
	P = 0;
	I = 0;
	D = 0;
	p = 0;
	i = 0;
	d = 0;
	value = val;
	shift = shft;
}
PID::PID(int16_t setpoint, int16_t prop, int16_t intgrl, int16_t diff, int16_t * val, uint8_t shft) {
	// TODO Auto-generated constructor stub
	sp = setpoint;
	P = prop;
	I = intgrl;
	D = diff;
	p = 0;
	i = 0;
	d = 0;
	value = val;
	shift = shft;
}
PID::~PID() {
	// TODO Auto-generated destructor stub
}


void PID::Update()
{
	// updates p, i, and d terms as well as the output value
	d = p;
	p = sp - *value;

	// if the value of the reading flipped sign, set integral term to zero
	if((d >= 0) ^ (p < 0))
	{
		i = 0;
	}
	// if the integral term is about to overflow/underflow, freeze it
	else if( (SHRT_MIN < i + p) and  (i + p < SHRT_MAX))
	{
		i += p;
	}
	d -= p;

	// assign PID filtered result to int16_t * value
	*value = (P*p + I * i + D * d) >> shift;
}


