/**
 * File: BlinkTask.cpp
 * Description:
 * SoftTimer library is a lightweight but effective event based timeshare solution for Arduino.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2017 Balazs Kelemen
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

#include "BlinkTask.h"
#include "SoftTimer.h"

#define BLINK_STATE_OFF  0
#define BLINK_STATE_ON   1
#define BLINK_STATE_WAIT 2

void BlinkTask::init(byte outPin, unsigned long onMs, unsigned long offMs, byte count, unsigned long delayMs) {
  this->onMs = onMs;
  this->offMs = offMs;
  this->count = count;
  this->delayMs = delayMs;

  pinMode(outPin, OUTPUT);
  this->_bitMask = digitalPinToBitMask(outPin);
  this->_portRegister = portOutputRegister(digitalPinToPort(outPin));

  this->onLevel = HIGH;
}

BlinkTask::BlinkTask(byte outPin, unsigned long onOffMs) : Task(onOffMs, &(BlinkTask::stepState)) {
  this->init(outPin, onOffMs, onOffMs, 0, 0);
}

BlinkTask::BlinkTask(byte outPin, unsigned long onMs, unsigned long offMs) : Task(onMs, &(BlinkTask::stepState)) {
  this->init(outPin, onMs, offMs, 0, 0);
}

BlinkTask::BlinkTask(byte outPin, unsigned long onMs,unsigned long offMs, byte count) : Task(onMs, &(BlinkTask::stepState)) {
  this->init(outPin, onMs, offMs, count, 0);
  this->stop();
}

BlinkTask::BlinkTask(byte outPin, unsigned long onMs, unsigned long offMs, byte count, unsigned long delayMs) : Task(onMs, &(BlinkTask::stepState)) {
  this->init(outPin, onMs, offMs, count, delayMs);
}

void BlinkTask::start() {
  this->_state = BLINK_STATE_OFF;
  this->_counter = 0;
  this->setPeriodMs(0);
  SoftTimer.add(this);
}

void BlinkTask::start(byte count) {
  this->count = count;
  this->start();
  this->delayMs = 0;
}

void BlinkTask::stop() {
  SoftTimer.remove(this);
}

void BlinkTask::stepState(Task* task) {
  BlinkTask* bt = (BlinkTask*)task;
  if(bt->_state == BLINK_STATE_ON) {
    // -- Turn off.
    if(bt->onLevel == HIGH) {
      *bt->_portRegister &= ~bt->_bitMask;
    } else {  
      *bt->_portRegister |= bt->_bitMask;
    }
    bt->_counter += 1;
    bt->_state = BLINK_STATE_OFF;
    bt->setPeriodMs(bt->offMs);
  }
  else {
    // -- state == OFF or WAIT
    // -- Turn on.
    if(bt->onLevel == HIGH) {
      *bt->_portRegister |= bt->_bitMask;
    } else {  
      *bt->_portRegister &= ~bt->_bitMask;
    }
    bt->_state = BLINK_STATE_ON;
    bt->setPeriodMs(bt->onMs);
  }
  if((bt->count > 0) && (bt->_counter >= bt->count)) {
    // -- Count was defined, and we reached it.
    bt->_counter = 0;
    
    if(bt->delayMs > 0) {
      // -- delay was defined.
      bt->_state = BLINK_STATE_WAIT;
      bt->setPeriodMs(bt->delayMs);
    } else {
      bt->stop();
    }
  }
}
