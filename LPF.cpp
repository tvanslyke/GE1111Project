/*
 * LPF.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: tim
 */

#include "LPF.h"

LPF::LPF(uint8_t factor)
{
	// bitshift factor
  this->factor = factor;

  // value of filtered result
  this->value = 0;
}



LPF::~LPF() {
	// TODO Auto-generated destructor stub
}
int16_t LPF::Filt(int16_t reading)
{
	// apply filter to most recent reading
	value += (int16_t)(reading - value) >> factor;
    return (int16_t)value;
}

