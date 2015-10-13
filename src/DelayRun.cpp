/**
 * File: DelayRun.cpp
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
#include "DelayRun.h"
#include <Task.h>

#define STATE_STARTING 0
#define STATE_ON_DELAY 1

DelayRun::DelayRun(unsigned long delayMs, boolean (*callback)(Task* task), DelayRun* followedBy)
    : Task(delayMs, &(DelayRun::step)) {
  this->delayMs = delayMs;
  this->_callback = callback;
  this->followedBy = followedBy;
}

void DelayRun::startDelayed() {
  this->_state = STATE_STARTING;
  this->setPeriodMs(0);
  SoftTimer.add(this);
}

void DelayRun::step(Task* task) {
  DelayRun* dr = (DelayRun*)task;
  if(dr->_state == STATE_STARTING) {
    dr->_state = STATE_ON_DELAY;
    dr->setPeriodMs(dr->delayMs);
    return; // -- Do not remove me from Timer Manager.
  } else if(dr->_state == STATE_ON_DELAY) {

    // -- Remove me from Timer Manager.
    SoftTimer.remove(dr);

    boolean retVal;
    if(dr->_callback != NULL) {
      retVal = dr->_callback(dr);
    } else {
      // -- If no callback was specified, than always start the followedBy task.
      retVal = true;
    }
    if(retVal) {
      if(dr->followedBy != NULL) {
        dr->followedBy->startDelayed();
      }
    }
  }
}
