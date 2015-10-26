/**
 * File: Rotary.cpp
 * Description:
 * SoftTimer library is a lightweight but effective event based timeshare solution for Arduino.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2015 Balazs Kelemen
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
#include "Rotary.h"
#include <Task.h>
#include <PciManager.h>

#define IDDLE_TIME_MICROS -1L

#define EVENT_NOTIFIED 0
#define EVENT_OCCURRED 1
#define EVENT_CLEARED  2


Rotary::Rotary(int pinA, int pinB, void (*onRotation)(short direction, Rotary* rotary), bool pullUp)
    : Task(IDDLE_TIME_MICROS, &(Rotary::step)) {
  this->_listenerA.init(pinA, this, pullUp);
  this->_listenerB.init(pinB, this, pullUp);
  this->_stateCW = EVENT_NOTIFIED;
  this->_stateCCW = EVENT_NOTIFIED;
  this->_onRotation = onRotation;
  
  PciManager.registerListener(pinA, &this->_listenerA);
  PciManager.registerListener(pinB, &this->_listenerB);

  SoftTimer.add(this);
}

void Rotary::pciHandleChange(byte changedTo, PciListenerImp2* listener) {
  if(listener == &this->_listenerB) {
    // -- pinB changes
    if((changedTo == HIGH) && (this->_listenerA.lastVal == LOW)) {
      if(this->_stateCW == EVENT_CLEARED) {
        this->_stateCW = EVENT_OCCURRED;
        this->periodMicros = 0;
      }
    }
    else if((changedTo == LOW) && (this->_listenerA.lastVal == HIGH)) {
      this->_stateCW = EVENT_CLEARED;
    }
  }
  if(listener == &this->_listenerA) {
    // -- pinA changes
    if((changedTo == HIGH) && (this->_listenerB.lastVal == LOW)) {
      if(this->_stateCCW == EVENT_CLEARED) {
        this->_stateCCW = EVENT_OCCURRED;
        this->periodMicros = 0;
      }
    }
    else if((changedTo == LOW) && (this->_listenerB.lastVal == HIGH)) {
      this->_stateCCW = EVENT_CLEARED;
    }
  }
}


void Rotary::step(Task* task) {
  Rotary* me = (Rotary*)task;

  if(me->_stateCW == EVENT_OCCURRED) {
    me->_onRotation(DIRECTION_CW, me);
    me->_stateCW = EVENT_NOTIFIED;
  }
  if(me->_stateCCW == EVENT_OCCURRED) {
    me->_onRotation(DIRECTION_CCW, me);
    me->_stateCCW = EVENT_NOTIFIED;
  }
  me->periodMicros = IDDLE_TIME_MICROS;
}

