/*
 * Filter.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: tim
 */


#include "Filter.h"
#include "HPF.h"
#include "LPF.h"


int BitCount(unsigned int u);



Filter::Filter(int16_t * raw, uint8_t * factors, uint8_t order, bool type) {
	// TODO Auto-generated constructor stub

	// value of current filtered result
	this->value = 0;

	// pointer to variable where input readings are stored
	this->raw = raw;

	// order of the filter (how many filters applied)
	this->order = order;

	// unsigned 32-bit int whose bit-sequence represents whether subsequent filters are
	// high-pass or low-pass.  0s correspond to low pass, 1s correspond to high pass.
	//
	// this constructor does not use this value.
	this->seq = 0;

	// type = true -> high pass
	// type = false -> low pass
	if(type)
	{
		this->lpfs = NULL;
		this->hpfs = (HPF *)malloc(this->order * sizeof(HPF));
		for(uint8_t i = 0; i < order; i++)
		{
			this->hpfs[i] = HPF(factors[i]);
		}
	}
	else
	{
		this->hpfs = NULL;
		this->lpfs = (LPF *)malloc(this->order * sizeof(LPF));
		for(uint8_t i = 0; i < order; i++)
		{
			this->lpfs[i] = LPF(factors[i]);
		}
	}

}


Filter::Filter(int16_t * raw, uint8_t * factors, uint8_t order, uint32_t binaryBool)
{
	this->value = 0;
	this->raw = raw;
	this->order = order;

	// unsigned 32-bit int whose bit-sequence represents whether subsequent filters are
	// high-pass or low-pass.  0s correspond to low pass, 1s correspond to high pass.
	this->seq = binaryBool;

	// helper counter variables used below
	uint8_t i, j;
	i = BitCount(binaryBool << (32-order));
	j = order - i;

	// alocate memory for high-pass and low-pass filter objects
	this->hpfs = (HPF *)malloc(i * sizeof(HPF));
	this->lpfs = (LPF *)malloc(j * sizeof(LPF));

	// initialize to zero
	i = 0;
	j = 0;

	// fill up hpfs and lpfs with HPF and LPF objects until complete
	while(i + j < order)
	{
		if( (binaryBool >> (i + j)) & 0x00000001)
		{
			this->hpfs[i] = HPF(factors[j + i]);
			i++;
		}
		else
		{
			this->lpfs[j] = LPF(factors[i+j]);
			j++;
		}
	}
}


Filter::Filter()
{
	// default constructor
	value = 0;
	raw = NULL;
	order = 0;
	lpfs = NULL;
	hpfs = NULL;
	seq = 0;
}
Filter::~Filter() {
	// TODO Auto-generated destructor stub
}


int16_t Filter::Filt()
{
	// filters the 'raw' value, assigns the fully filtered result
	// to 'value' and returns the value.

	value = *raw;

	// if both lists are null, simply return
	if(lpfs == NULL and hpfs == NULL)
	{
		return (int16_t)value;
	}
	// exclusively high-pass
	else if(lpfs == NULL)
	{
		for(uint8_t i = 0; i < order; i++)
		{
			value = hpfs[i].Filt((int16_t)value);

		}
	}
	// exclusively low pass
	else if (hpfs == NULL)
	{
		for(uint8_t i = 0; i < order; i++)
		{
			value = lpfs[i].Filt((int16_t)value);

		}
	}
	// both high and low pass filters should be applied in this case, according
	// to the sequence of 'seq'
	else
	{
		uint8_t i, j;
		i = 0;
		j = 0;
		// iterate until done
		while(i + j < order)
		{
			// select filter according to the next bit in 'seq'
			if( (seq >> (i + j)) & 0x00000001)
			{
				value = this->hpfs[i].Filt((int16_t)value);
				i++;
			}
			else
			{
				value = this->lpfs[j].Filt((int16_t)value);
				j++;
			}
		}
	}
	return (int16_t)value;
}

// helper function that counts the number of bits in a number in constant-time
int BitCount(unsigned int u)
{
     unsigned int uCount;

     uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
     return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}
