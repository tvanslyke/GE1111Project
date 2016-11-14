/*
 * Alarm.h
 *
 *  Created on: Nov 12, 2016
 *      Author: tim
 *
 *		Class for controlling behavior of speaker/beeper
 *		as an 'alarm' of sorts.
 */

#ifndef ALARM_H_
#define ALARM_H_


class Alarm {
private:
	// analog output pin to the speaker
	uint8_t alarmPin;

	// PWM value conroling volume of the speaker
	uint8_t tone;
public:
	Alarm(uint8_t alarmPin);
	virtual ~Alarm();

	// initializer
	void Begin();

	// sends tone to speaker with specified duration
	void Beep(uint16_t);

	// sets the volume
	void SetTone(uint8_t);
};

#endif /* ALARM_H_ */
