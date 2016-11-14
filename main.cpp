/*
 * main.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: tim
 */


#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/variants/standard/pins_arduino.h"

#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19
HardwareSerial Serial;







#include "Filter.h"
//#include <LiquidCrystal.h>
#include "LCDManager.h"
#include "Sensor.h"
#include "string.h"
#include "PID.h"

// LCD Screen Functionality
LiquidCrystal lcd(12, 11, 6, 7, 8, 9);

// LCD Manager class for smooth UI functionality
LCDManager lcdm(&lcd);

// Low pass filter bitshift constants for the temperature sensor
uint8_t factors[1] = {1};

// Low pass filter for reducing noise in temperature sensor
Filter tempFilter;

// Temperature sensor for handling ADC reading
Sensor tempSensor(A0);

// char array buffer for the default message
char defaultMessage[40];

int16_t motorSpeed;
PID pid()

float temp = 0;


float cvtTemp(int16_t tempReading)
{
  // 600 -> 37 C
  // 211 -> 0  C
  return  0.095115681 * (tempReading - 211);
}

void LastMessage();


void NextMessage();

void Update();

void UpdateDefaultMessage()
{
  tempSensor.Read();

  sprintf(defaultMessage, "Temp: %6i C  Messages: %6i", (int)cvtTemp(tempFilter.Filt()), lcdm.HowMany());
  Serial.println(defaultMessage);
  lcdm.SetDefault(defaultMessage);
}
void setup()
{
Serial.begin(9600);

  tempFilter = Filter(tempSensor.Address(), factors, 1, false);
  lcdm.NewMessage("One                             ");
  lcdm.NewMessage("Two                             ");
  Serial.println("begin");
  tempSensor.Read();
  Serial.println(lcdm.HowMany());
  sprintf(defaultMessage, "Temp: %6i C  Messages: %6i", (int)cvtTemp(tempFilter.Filt()), lcdm.HowMany());
  Serial.println("begin");
  lcdm.Begin(defaultMessage);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), NextMessage, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), LastMessage, FALLING);
}


void loop()
{
  UpdateDefaultMessage();
  delay(100);
}



void LastMessage()
{
  lcdm.Last();
}

void NextMessage()
{
  lcdm.Next();
}






