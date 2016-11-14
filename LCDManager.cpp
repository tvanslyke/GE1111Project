/*
 * LCDManager.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: tim
 */

#include "LCDManager.h"
#include "string.h"
#include "/home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/Arduino.h"
#define CHARS  160
#define MSGS   4


LCDManager::LCDManager(LiquidCrystal * lcd){

	// pointer to LiquidCrystal object
	this->lcd = lcd;
	// message buffer.  Each message is 32 chars long
	this->messages = (char *)malloc(5 * 32 * sizeof(char));
	// initialize each char to ASCII-32 (space/blank)
	memset(messages, 0, 5 * 32 * sizeof(char));
	// index in messages/message buffer
	this->msgNum = 0;
	// number of non-default messages in message buffer
	this->msgCount = 0;
	// bool indicating whether urgent mode is active.
	this->urgent = false;
}

LCDManager::~LCDManager() {
	// TODO Auto-generated destructor stub
}


void LCDManager::Begin(char * message)
{
	// initializes LiquidCrystal object pointed to by lcd and writes the default message
	// to the LCD.

  lcd->begin(16, 2);
  delay(500);
  this->SetDefault(message);
  delay(500);
  this->Write();
}


uint8_t LCDManager::HowMany()
{
	// returns the number of messages in the message buffer

	return this->msgCount;
}


uint8_t LCDManager::WhichOne()
{
	// returns which non-default message is currently displayed

	return this->msgNum;
}


void LCDManager::Write()
{
	// writes the message at index msgNum to the LCD screen

  if(not urgent)
  {
    lcd->setCursor(0,0);
    for(uint8_t i = (32 * msgNum); i < (32 * msgNum) + 16; i++)
  	{
  	  lcd->print(messages[i]);
  	}
  	lcd->setCursor(0,1);
  	for(uint8_t i = (32 * msgNum) + 16; i < (32 * msgNum) + 32; i++)
    {
      lcd->print(messages[i]);
    }
    lcd->setCursor(0,0);
  }
}


bool LCDManager::NewMessage(char * message)
{
	// adds a new message to the message buffer, given that there is room in the buffer

	if(msgCount == MSGS)
	{
		return false;
	}
	else
	{
    msgCount++;
		uint32_t offset = 32 * (msgCount);
		for(uint8_t i = offset; i < offset + 32; i++)
		{
			messages[i] = message[i-offset];
		}

	}
	return true;
}


void LCDManager::SetDefault(char * message)
{
	// sets a new message to the default message

	for(uint8_t i = 0; i < 32; i++)
	{
		messages[i] = message[i];
	}
}


void LCDManager::Urgent(char * message)
{
	// turns urgent mode on with a message passed in as an argument.
	// in urgent mode, only the Display() method can overwrite the screen

	urgent = true;
	this->Display(message);
}


void LCDManager::Relax()
{
	// exits urgent mode and writes the current message at index msgNum to the screen

	urgent = false;
	this->Write();
}


void LCDManager::Display(char * message)
{
  // forces a message not currently in the message buffer to be displayed to the screen

  if(not urgent)
  {
    lcd->setCursor(0,0);
    for(uint8_t i = 0; i < 16; i++)
    {
      lcd->print(message[i]);
    }
    lcd->setCursor(0,1);
    for(uint8_t i = 16; i <  32; i++)
    {
      lcd->print(message[i]);
    }
  }
}


bool LCDManager::Delete()
{
	// deletes the message at index msgNum from the message buffer, except when
	// msgNum is zero.  The default message cannot be deleted.

	if(urgent)
	{
		return true;
	}
	else if(not (msgCount == 0 or msgNum == 0))
	{

		for(uint8_t i = msgNum * 32; i < CHARS - 32; i++ )
    {
      messages[i] = messages[i + 32];
    }
    memset((messages + CHARS - 32), 32, 32);
    msgCount--;
    this->Write();
    return true;
	}
	else
	{
		return false;
	}
}


bool LCDManager::Next()
{
	// increments msgNum and displays the next appropriate message, given
	// that the current message is not the last message

	if(msgNum < msgCount)
	{
		msgNum++;
		this->Write();
		return true;
	}
	else
	{
		return false;
	}
}


bool LCDManager::Last()
{
	// decrements msgNum and displays the previous message, given that
	// the current message is not the first (default) message.

	if(msgNum > 0)
	{
		msgNum--;
		this->Write();
		return true;
	}
	else
	{
		return false;
	}
}
