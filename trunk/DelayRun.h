/**
 * File: DelayRun.h
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

#ifndef DELAYRUN_H
#define DELAYRUN_H

#include <SoftTimer.h>
#include <Task.h>
#include <Arduino.h>

/**
 * Run a callback after a specified delay. The task will stop when finished. Also chains tasks.
 */
class DelayRun : public Task
{
  public:
    /**
     * Setup a delayed task.
     *  delayMs - The callback will be launched after this amount of milliseconds was passed.
     *    A value zero (0) may also have sense, when you only want to chain tasks.
     *    Do not add values greater then 4,294,967, which is about 71 minutes!
     *  callback - The function to call after the specified time-span. Optional, may be NULL.
     *    The return value of the callback controls behavior of the "followedBy" option.
     *  followedBy - If the followedBy was specified, than it will be started when this was finished.
     *   Starting the followedBy can be denied by returning FALSE in the callback.
     */
    DelayRun(unsigned long delayMs, boolean (*callback)(Task* task), DelayRun* followedBy = NULL);

    /**
      * Register the task, and start waiting for the delayMs to pass.
      * If you need to prevent the task to start, you need to remove it from the
      * Timer Manager (with the SoftTimer.remove() function).
      */
    void startDelayed();


    /**
     * The time to sleep the task before launching the callback.
     * Do not set values greater then 4,294,967, which is about 71 minutes!
     */
    unsigned long delayMs;
    /** The task should be started after this one was finished. */
    DelayRun* followedBy;

  private:
    boolean (*_callback)(Task* task);
    static void step(Task* me);

    byte _state;
};

#endif

