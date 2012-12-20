/**
 * File: Debouncer.cpp
 * Description:
 * SoftTimer library is a lightweight but effective event based timeshare solution for Arduino.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2012 Balazs Kelemen
 * Copying permission statement:
    This file is part of SoftTimer.

    SoftTimer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Arduino.h"
#include "Debouncer.h"
#include <DelayRun.h>

Debouncer::Debouncer(int pin, int pushMode, void (*onPressed)(), void (*onReleased)(unsigned long pressTimespan))
    : DelayRun(DEFAULT_DEBOUNCE_DELAY_MILLIS, &(Debouncer::step)) {
  this->_pin = pin;
  this->_state = STATE_OFF;
  this->_onLevel = pushMode;
  this->_onPressed = onPressed;
  this->_onReleased = onReleased;
  
  pinMode(pin, INPUT);
}

void Debouncer::pciHandleInterrupt(byte vect) {
  if((this->_state == STATE_OFF) || (this->_state == STATE_ON)) {
    int oppositeLevel = this->_state == STATE_OFF ? this->_onLevel : !this->_onLevel;
    // -- Test pin level, probably more pins are used by this interrupt.
    volatile int val = digitalRead(this->_pin);
    if(val == oppositeLevel) {
      if(this->_state == STATE_OFF) {
        this->_pressStart = millis(); // -- Save the first time to the start of this task.
      }
      // -- After pin change we have the opposite level, lets start the bouncing timespan.
      this->_state += 1;
      this->startDelayed();
    }
  }
}

boolean Debouncer::step(Task* task) {
  Debouncer* debouncer = (Debouncer*)task;
  int val = digitalRead(debouncer->_pin);
  if(debouncer->_state == STATE_OFFON_BOUNCING) {
    if(val == debouncer->_onLevel) {
    
      // -- Still pressing.
      debouncer->_state = STATE_ON;
      
      // -- Call the callback.
      if(debouncer->_onPressed != NULL) {
        debouncer->_onPressed();
      }
    } else {
    
      // -- Released while bouncing.
      debouncer->_state = STATE_OFF;
    }
  }
  else if(debouncer->_state == STATE_ONOFF_BOUNCING) {
    if(val == !debouncer->_onLevel) {
    
      // -- Really released.
      debouncer->_state = STATE_OFF;
      
      // -- Call the callback.
      if(debouncer->_onReleased != NULL) {
        volatile unsigned long pressTimespan = millis() - debouncer->_pressStart; // -- If millis() overflows this calculation will be still good.
        debouncer->_onReleased(pressTimespan);
      }
    } else {
    
      // -- Repressed while bouncing.
      debouncer->_state = STATE_ON;
    }
  }
  return false;
}

boolean Debouncer::setDebounceDelayMs(unsigned long debounceDelayMs) {
  this->setPeriodMs(debounceDelayMs);
}