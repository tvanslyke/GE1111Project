/*
 * Filter.h
 *
 *  Created on: Nov 4, 2016
 *      Author: tim
 *
 *      	Class for cleaning up sensor readings with efficient
 *      	filtering functions that require minimal state to be
 *      	effective.  The class requires implementation of LPF
 *      	and HPF classes to operate.
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"
#include "stdint.h"
#include "stdlib.h"
#include "Sensor.h"
#include "LPF.h"
#include "HPF.h"


class Filter{
private:

	// pointer to raw value to be filtered
	int16_t * raw;

	// pointer to one or more LPF objects that will be applied to the input one
	// after another in tandem (or not) with the HPF objects in HPF * hpfs.
	LPF * lpfs;

	// pointer to one or more HPF objects that will be applied to the input one
	// after another in tandem (or not) with the LPF objects in LPF * lpfs.
	HPF * hpfs;

	// value of the filtered output (after applying all of the perscribed
	// filtering functions)
	int32_t value;

	// order of the filter (sum total of the number of LPF and HPF objects pointed to)
	uint8_t order;

	// 32 bit int indicating the sequence of high and low pass filters.
	uint32_t seq;

public:

	Filter(int16_t * raw, uint8_t * factors, uint8_t order, bool type);
	Filter(int16_t * raw, uint8_t * factors, uint8_t order, uint32_t binaryBool);
	Filter();
	virtual ~Filter();

	// filtering function
	int16_t Filt();
};



#endif /* FILTER_H_ */
