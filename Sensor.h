/*
 * Sensor.h
 *
 *  Created on: Nov 4, 2016
 *      Author: tim
 *
 *      	Generic class for analog sensors, intended to be inherited from.
 *
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include "stdint.h"
#include "stdlib.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"

class Sensor {
private:

	// analog pin to make readings on
	uint8_t pin;
public:
	// value of previous reading
	int16_t lastReading;
	Sensor(uint8_t);
	Sensor();
	virtual ~Sensor();

	// returns the address of 'lastReading'
	int16_t * Address();

	// stores a new reading in 'lastReading' and returns the value
	virtual int16_t Read();
};

#endif /* SENSOR_H_ */
