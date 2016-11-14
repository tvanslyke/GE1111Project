/*
 * Sensor.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: tim
 */

#include "Sensor.h"

Sensor::Sensor(uint8_t pin) {
	// TODO Auto-generated constructor stub

	// analog pin for reading voltage
	this->pin = pin;

	// value of last reading (should be 0-1023)
	lastReading = 0;
}
Sensor::Sensor() {
	// default constructor

	this->pin = 14;
	lastReading = 0;
}
Sensor::~Sensor() {

	// TODO Auto-generated destructor stub
}

int16_t * Sensor::Address()
{
	// returns the address of member 'lastReading' for use in
	// Filter and PID objects

	return &lastReading;
}
int16_t Sensor::Read()
{
	// Reads and returns a new voltage from the analog pin

	return lastReading;
}

