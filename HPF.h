/*
 * HPF.h
 *
 *  Created on: Nov 8, 2016
 *      Author: tim
 *
 *      	Class for applying a discrete, first-order high-pass filter
 *     		to a constantly changing value.  Holds all relevant state for
 *     		the necessary filtering.  Uses efficient, non-floating point
 *     		arithmetic to accomplish this.
 */

#ifndef HPF_H_
#define HPF_H_

#include "stdint.h"
#include "stdlib.h"

class HPF
{
private:
	// value of the filtered output
	int32_t  value;

	// value of the most recent unfiltered input
	int16_t lastReading;

	// bitshift factor applied during filtering function.
	// a method of bitshifting is used instead of multiplying by a decimal
	// because the operation is significantly faster.  multiplying by .25 is
	// the same as bitshifting rightward by two places, for instance
	uint8_t  factor;
public:
	HPF(uint8_t factor);
	HPF();
	virtual ~HPF();

	// filtering function
    int16_t Filt(int16_t);
};

#endif /* HPF_H_ */
