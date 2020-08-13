#include "Arduino.h"
#include "runOnMorse.h"

runOnMorse::runOnMorse(int pin)
{
	pinMode(pin, INPUT_PULLUP);
	_pin = pin;

	dashLength = 125;
	runTime = 150;

	_debounceDelay = 10;
}

unsigned long long runOnMorse::getCode()
{
	bool reading = digitalRead(_pin);
	unsigned long time = millis();
	unsigned long long c = 0;

	if (reading != _lastButtonState) {
		_lastDebounceTime = time;
	}

	if ((time - _lastDebounceTime) > _debounceDelay) {
		if (reading != _buttonState) {
			_buttonState = reading;
			if (_buttonState == LOW) {  // FALLING
				_pressTime = time;
			} else {					// RISING
				_releaseTime = time;
				_morseInput = (10 * _morseInput) + _dotOrDash();
			}
		}
	}

	if ((time - _releaseTime) >= runTime && _buttonState == HIGH) {
		c = _morseInput;
		_morseInput = 0;
	} else {
		c = 0;
	}

	_lastButtonState = reading;

	return c;
}

int runOnMorse::_dotOrDash() 
{
	unsigned long t = _releaseTime - _pressTime;
	if (t >= dashLength) {
		return 2;
	} else {
		return 1;
	}
}