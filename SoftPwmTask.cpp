/**
 * File: SoftPwmTask.cpp
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

#include "SoftTimer.h"
#include "SoftPwmTask.h"

SoftPwmTask::SoftPwmTask(int pin) : Task(0, &(SoftPwmTask::step))
{
  _outPin = pin;
  _value = 0;
  _counter = 0;
  upperLimit = 255;
  pinMode(_outPin, OUTPUT);
  this->periodMicros = 30;

  _bitMask = digitalPinToBitMask(pin);
  _portRegister = portOutputRegister(digitalPinToPort(pin));
}


void SoftPwmTask::analogWrite(byte value) {
  this->_value = value;
}

void SoftPwmTask::off() {
   *this->_portRegister &= ~this->_bitMask;
 }

void SoftPwmTask::step(Task* task)
{
  SoftPwmTask* spt = (SoftPwmTask*)task;
  if(spt->_counter == spt->upperLimit) {
    // -- Reached the upper limit.
    if(spt->_value != 0) {
      // -- Set to HIGH.
      *spt->_portRegister |= spt->_bitMask;
    }
    spt->_counter = 0;
  }
  else {
    if(spt->_counter >= spt->_value) {
      // -- Reached the value level.
      // -- Set to LOW.
      *spt->_portRegister &= ~spt->_bitMask;
    }
    spt->_counter++;
  }
}
