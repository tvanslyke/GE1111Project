/*
 * HPF.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: tim
 */

#include "HPF.h"



HPF::HPF(uint8_t factor) {
	// TODO Auto-generated constructor stub

	// bitshift factor applied to readings.
	this->factor = factor;

	// value of filtered reading
	this->value = 0;

	// stores previous raw reading
	this->lastReading = 0;
}

HPF::~HPF() {
	// TODO Auto-generated destructor stub
}


int16_t HPF::Filt(int16_t reading)
{
	// apply filtering function to most recent reading

	value = (int16_t)(value + (reading - lastReading)) >> factor;
	lastReading = reading;
	return (int16_t)value;
}
