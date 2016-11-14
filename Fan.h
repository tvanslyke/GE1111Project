/*
 * Fan.h
 *
 *  Created on: Nov 12, 2016
 *      Author: tim
 *
 *      	Class for controlling fan with a simple transistor motor driver.
 *
 */

#ifndef FAN_H_
#define FAN_H_

class Fan {
private:
	// output pin to motor driver
	uint8_t writePin;

	// PWM value 0-255
	uint16_t * speed;

	// indicates whether fan can be turned on at this time
	bool isOn;
public:
	Fan(uint8_t pin, int16_t * speed);
	virtual ~Fan();

	// initiliazer to be used in 'void setup()'
	void Begin();

	// runs the fan given that 'isOn' is set to true
	void Run();

	// turns fan off
	void Off();

	// turns fan on
	void On();

	// returns whether fan is on
	bool IsRunning();
};

#endif /* FAN_H_ */
