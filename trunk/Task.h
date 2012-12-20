/**
 * File: Task.h
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

#ifndef TASK_H
#define TASK_H

/**
 * Task is a job that should be called repeatedly,
 */
class Task
{
  public:
    /**
     * Construct a task with defining a period and a callback handler function.
     *  periodMs - Call the task in every X milliseconds. Do not add values greater then 4,294,967, which is about 71 minutes!
     *  callback - Is a static function reference, the function will be called each time. The callback function need to
     * have one argument, which is the currently running task.
     */
    Task(unsigned long periodMs, void (*callback)(Task* me));
    
    /**
     * The timeslot in milliseconds the handler should be called.
     * Do not add values greater then 4,294,967, which is about 71 minutes!
     */
    void setPeriodMs(unsigned long periodMs);

    /**
     * The timeslot in milliseconds the handler should be called. If the value is near 1 the handler will be called in every loop.
     */
    unsigned long periodMicros;
    
    /**
     * The last call (start) time of the task. You can reset the task by setting this value to micros().
     */
    volatile unsigned long lastCallTimeMicros;
    
    /**
     * The function that will be called when the period time was passed since the lastCallTime. This member is for internal use only.
     */
    void (*callback)(Task* me);
    /**
     * This member is for internal use only. Do not change!
     */
    Task* nextTask;
  private:
};

#endif
