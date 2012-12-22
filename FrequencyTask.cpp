/**
 * File: FrequencyTask.cpp
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
#include "FrequencyTask.h"

FrequencyTask::FrequencyTask(int outPin, float freq) : Task(0, &(FrequencyTask::step))
{
  pinMode(outPin, OUTPUT);
  
  _bitMask = digitalPinToBitMask(outPin);
  _portRegister = portOutputRegister(digitalPinToPort(outPin));
  
  this->setFrequency(freq);
}


void FrequencyTask::setFrequency(float freq) {
  this->periodMicros = 500000.0 / freq;
}

void FrequencyTask::step(Task* task)
{
  FrequencyTask* ft = (FrequencyTask*)task;
  
  // -- Invert state.
  if(ft->_stateOn) {
      *ft->_portRegister &= ~ft->_bitMask;
  } else {
      *ft->_portRegister |= ft->_bitMask;
  }
  
  ft->_stateOn = !ft->_stateOn;
}

