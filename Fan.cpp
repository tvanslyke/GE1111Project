/*
 * Fan.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: tim
 */

#include "Fan.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"

Fan::Fan(uint8_t writePin, int16_t * speed) {
	// TODO Auto-generated constructor stub

	// pin output to motor driver (PWM-write)
	this->writePin = writePin;

	// unsigned 8-bit int indicating pulse-width sent to motor driver
	this->speed = speed;

	// master on-off bool.  prevents motor from moving when set to false.
	this->isOn = false;
}

Fan::~Fan() {
	// TODO Auto-generated destructor stub
}


void Fan::Begin()
{
	// initialize writePin to output
	pinMode(writePin, OUTPUT);
}
void Fan::Run()
{
	// turns the fan if 'isOn' is set to true.
	if(isOn)
	{
		analogWrite(writePin, (uint8_t)speed);
	}
}
void Fan::Off()
{
	// shuts fan off

	isOn = false;
}
void Fan::On()
{
	// turns fan on

	isOn = true;
}
bool Fan::IsRunning()
{
	// gets status of fan

	return isOn;
}
