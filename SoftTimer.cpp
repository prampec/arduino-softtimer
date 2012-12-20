/**
 * File: SoftTimer.cpp
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
#include "SoftTimer.h"

/**
 * The main loop is implemented here. You do not ever need to call implement this function
 * if you think in event driven programing.
 */
void loop() {
  SoftTimer.run();
}


/**
 * Register a task in the timer manager.
 */
void SoftTimerClass::add(Task* task) {

  // -- A task should be registered only once.
  this->remove(task);
  
  if(this->_tasks == NULL) {
  
    // -- This is the first task being registered.
    this->_tasks = task;
    
  } else {
  
    Task* lastTask = this->_tasks;
    // -- Find the last task, to build a chain.
    while(lastTask->nextTask != NULL) {
      lastTask = lastTask->nextTask;
    }
    // -- Last task found, let's add this task to the end of the chain.
    lastTask->nextTask = task;
    
  }
  
  task->lastCallTimeMicros = micros() - task->periodMicros; // -- Start immediately after registering.
  task->nextTask = NULL;
}


/**
 * Remove registration of a task in the timer manager.
 */
void SoftTimerClass::remove(Task* task) {
  if(this->_tasks != NULL) {
    if(this->_tasks == task) {
      // -- This was the first task.
      this->_tasks = task->nextTask;
    } else {
      Task* lastTask = this->_tasks;
      // -- Find this task in the chain.
      while(lastTask->nextTask != NULL) {
        if(lastTask->nextTask == task) {
          // -- Remove the task with joining the chain.
          lastTask->nextTask = task->nextTask;
          break;
        }
        lastTask = lastTask->nextTask;
      }
    }
  }
}

/**
 * Walk through the chain looking for task to call.
 */
void SoftTimerClass::run() {
  Task* task = this->_tasks;
  // -- (If this->_tasks is NULL, than nothing is registered.)
  while(task != NULL) {
    this->testAndCall(task);
    task = task->nextTask;
  }
}

/**
 * Test a task and call the callback if its period was passed since last call.
 */
void SoftTimerClass::testAndCall(Task* task) {
  unsigned long now = micros();
  unsigned long calc = task->lastCallTimeMicros + task->periodMicros;
  if(
    ((now >= calc) && (
      (calc >= task->lastCallTimeMicros) // -- Nothing was overflown.
      || (task->lastCallTimeMicros > now) // -- Both timer and interval-end overflows
      ))
    || ((now < task->lastCallTimeMicros) && (task->lastCallTimeMicros <= calc))) // -- timer overflows, but interval-end does not
  {
    task->callback(task);
    task->lastCallTimeMicros = now;
  }
}


/**
 * Create a singleton from this manager class.
 */
SoftTimerClass SoftTimer;
