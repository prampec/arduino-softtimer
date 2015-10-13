/**
 * File: Dimmer.cpp
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
#include "Dimmer.h"

Dimmer::Dimmer(SoftPwmTask* pwm, int frequencyMs) : Task(10, &(Dimmer::step))
{
  this->_pwm = pwm;
  this->direction = DIMMER_DIRECTION_HIGH;
  this->value = 0;
  this->_pwm->analogWrite((byte)this->value);
  this->stepCount = DEFAULT_STEP_COUNT;

  this->setFrequency(frequencyMs);
}


void Dimmer::startPulsate() {
  this->stopOnLimit = false;
  SoftTimer.add(this->_pwm);
  SoftTimer.add(this);
}

void Dimmer::hold() {
  SoftTimer.remove(this);
}

void Dimmer::off() {
  this->hold();
  this->_pwm->off();
  SoftTimer.remove(this);
  SoftTimer.remove(this->_pwm);
}

void Dimmer::revertDirection() {
  this->direction *= -1;
}

void Dimmer::setFrequency(int frequencyMs) {
  this->_stepLevel = (float)this->_pwm->upperLimit / (float)this->stepCount;
  this->periodMicros = (float)frequencyMs * 500.0 / (float)this->stepCount;
  
}

byte Dimmer::getUpperLimit() {
  return this->_pwm->upperLimit;
}


void Dimmer::step(Task* task)
{
  Dimmer* dimmer = (Dimmer*)task;
  
  boolean isOnLimit = false;
  
  dimmer->value += dimmer->direction * dimmer->_stepLevel;
  if((dimmer->direction < 0) && (dimmer->value < 0)) {
    dimmer->value = 0;
    dimmer->direction *= -1; // -- next time go in the other direction
    isOnLimit = true;
  } else if((dimmer->direction > 0) && (dimmer->value > dimmer->_pwm->upperLimit)) {
    dimmer->value = dimmer->_pwm->upperLimit;
    dimmer->direction *= -1; // -- next time go in the other direction
    isOnLimit = true;
  }
  
  dimmer->_pwm->analogWrite((byte)dimmer->value);
  
  if(isOnLimit && dimmer->stopOnLimit) {
    SoftTimer.remove(dimmer);
  }

}

