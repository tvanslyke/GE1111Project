/*
 * LCDManager.h
 *
 *  Created on: Nov 10, 2016
 *      Author: tim
 *
 *      Busy class used to manage the responsibilities of the LiquidCrystal object
 *      with respect to this application.  Includes a message buffer, a way to toggle
 *      through the messages in the buffer, functions for managing memory, and utilities
 *      for controlling/restricting the display.
 */

#ifndef LCDMANAGER_H_
#define LCDMANAGER_H_
#include "LiquidCrystal.h"
#include "stdlib.h"

class LCDManager {

private:
	// pointer to Liquid Crystal object
	LiquidCrystal * lcd;

	// message buffer.  Each message is 32 chars long.
	// must hold at least one default message
	char * messages;

	// index of current message selected and
	// the total number of non-default messages
	uint8_t msgNum, msgCount;

	// true when 'urgent mode' is active.  During urgent mode,
	// the LCD will not accept calls to the Write() method
	bool urgent;
	void Write();
public:
	LCDManager(LiquidCrystal * lcd);
	virtual ~LCDManager();

	// initializer to be used in 'void setup()'
    void Begin(char * message);

    // adds a message to the message buffer, given that there is space
	bool NewMessage(char * message);

	// starts urgent mode and forces the input message to the display
	void Urgent(char *);

	// sets the default message
	void SetDefault(char *);

	// disables urgent mode and writes the message at index 'msgNum' to
	// the display
	void Relax();

	// forces the input message to the display, regardless of the 'urgent' status
	void Display(char *);

	// deletes the current message (will not delete the default message)
	bool Delete();

	// increments to the next message if there is one
	bool Next();

	// decrements to the previous message if there is one
	bool Last();

	// returns the number of non-default messages in the message buffer
	uint8_t HowMany();

	// returns the index of the current message in the message buffer
	uint8_t WhichOne();
};

#endif /* LCDMANAGER_H_ */
