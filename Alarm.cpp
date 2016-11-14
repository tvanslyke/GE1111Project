/*
 * Alarm.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: tim
 */

#include "Alarm.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"


Alarm::Alarm(uint8_t alarmPin) {
	// TODO Auto-generated constructor stub

	// pin output for driving speaker
	this->alarmPin = alarmPin;
	// tone (PWM) 0-255.  0 is quieter, 255 is louder
	this->tone = 255;
}

Alarm::~Alarm() {
	// TODO Auto-generated destructor stub
}
void Alarm::Begin()
{
	// set the alarm pin to output
	pinMode(alarmPin, OUTPUT);
}
void Alarm::Beep(uint16_t duration)
{
	// drive the alarm for 'duration' milliseconds
	analogWrite(alarmPin, tone);
	delay(duration);
	analogWrite(alarmPin, 0);
}
void Alarm::SetTone(uint8_t tone)
{
	// change the tone of the alarm
	this->tone = tone;
}
