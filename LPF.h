/*
 * LPF.h
 *
 *  Created on: Nov 6, 2016
 *      Author: tim
 *
 *      	Class for applying a discrete, first-order low-pass filter
 *     		to a constantly changing value.  Holds all relevant state for
 *     		the necessary filtering.  Uses efficient, non-floating point
 *     		arithmetic to accomplish this.
 */

#ifndef LPF_H_
#define LPF_H_

#include "stdint.h"
#include "stdlib.h"
//#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"
class LPF
{
private:

	// value of the last filtered output
	int32_t  value;

	// bitshift factor applied during filtering function.
	// a method of bitshifting is used instead of multiplying by a decimal
	// because the operation is significantly faster.  multiplying by .25 is
	// the same as bitshifting rightward by two places, for instance
	uint8_t  factor;
public:
	LPF(uint8_t factor);
	virtual ~LPF();

	// filtering function
    int16_t Filt(int16_t);
};

#endif /* LPF_H_ */
