/**
 * File: HardDimmer.cpp
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
#include "HardDimmer.h"

HardDimmer::HardDimmer(int pwmPin, int frequencyMs) : Task(10, &(HardDimmer::step))
{
  this->_pwmPin = pwmPin;
  this->direction = DIMMER_DIRECTION_HIGH;
  this->value = 0;
  pinMode(this->_pwmPin, OUTPUT);
  this->stepCount = DEFAULT_STEP_COUNT;

  this->setFrequency(frequencyMs);
}


void HardDimmer::startPulsate() {
  this->stopOnLimit = false;
  analogWrite(this->_pwmPin, (int)this->value);
  SoftTimer.add(this);
}

void HardDimmer::hold() {
  SoftTimer.remove(this);
}

void HardDimmer::off() {
  this->hold();
  digitalWrite(this->_pwmPin, LOW);
  SoftTimer.remove(this);
}

void HardDimmer::revertDirection() {
  this->direction *= -1;
}

void HardDimmer::setFrequency(int frequencyMs) {
  this->_stepLevel = (float)(this->_topLevel - this->_bottomLevel) / (float)this->stepCount;
  this->periodMicros = (float)frequencyMs * 500.0 / (float)this->stepCount;
  /*
  Serial.print("Dimmer");
  Serial.print(this->_pwmPin);
  Serial.print(": stepLevel= ");
  Serial.print(this->_stepLevel);
  Serial.print(", periodMicros= ");
  Serial.println(this->periodMicros);
  */
}

byte HardDimmer::getUpperLimit() {
  return 255;
}


void HardDimmer::step(Task* task)
{
  HardDimmer* dimmer = (HardDimmer*)task;
  
  boolean isOnLimit = false;
  
  dimmer->value += dimmer->direction * dimmer->_stepLevel;
  if((dimmer->direction < 0) && (dimmer->value < dimmer->_bottomLevel)) {
    dimmer->value = dimmer->_bottomLevel;
    dimmer->direction *= -1; // -- next time go in the other direction
    isOnLimit = true;
  } else if((dimmer->direction > 0) && (dimmer->value > dimmer->_topLevel)) {
    dimmer->value = dimmer->_topLevel;
    dimmer->direction *= -1; // -- next time go in the other direction
    isOnLimit = true;
  }
  
  // Serial.print("Dimmer");
  // Serial.print(dimmer->_pwmPin);
  // Serial.print(" = ");
  // Serial.println((int)dimmer->value);
  analogWrite(dimmer->_pwmPin, (int)dimmer->value);
  
  if(isOnLimit && dimmer->stopOnLimit) {
    SoftTimer.remove(dimmer);
  }

}

