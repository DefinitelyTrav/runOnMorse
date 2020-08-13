/*
	runOnMorse.h - A library allowing the user to convert morse code inputs to user-defined functions.
	Created by Travis Wright, August 13, 2020
	Released into the public domain. 
*/
#ifndef runOnMorse_h
#define runOnMorse_h

#include "Arduino.h"

class runOnMorse
{
	public:
		runOnMorse(int pin);

		unsigned long long getCode();

		unsigned long dashLength;
		unsigned long runTime;
	
	private:
		int _pin;

		unsigned long long _morseInput;

		unsigned long _pressTime;
		unsigned long _releaseTime;

		int _dotOrDash();

		// Debounce stuff
		bool _buttonState;
		bool _lastButtonState;
		unsigned long _lastDebounceTime;
		unsigned long _debounceDelay;
};

#endif