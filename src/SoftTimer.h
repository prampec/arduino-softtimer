/**
 * File: SoftTimer.h
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

#ifndef SOFTTIMER_H
#define SOFTTIMER_H

#include "Arduino.h"

// -- With preventing loop() iteration you will benefit some milliseconds.
// -- On the other hand some platforms might depend on the loop(). If you are
// -- facing with unexpected problems, you might want to try enabling this macro.
// -- ENABLE_LOOP_ITERATION is disabled by default.
//#define ENABLE_LOOP_ITERATION

// -- By default the next start of a task scheduled from the beginning of the previous
// -- execution. But executions might shift if another task does not finish in time.
// -- With STRICT_TIMING the next execution is scheduled at the expected time.
// -- STRICT_TIMING is disabled by default, as it might likely to cause starvation.
//#define STRICT_TIMING

#include "Task.h"

class SoftTimerClass
{
  public:
    /**
     * Register a task in the timer manager.
     */
    void add(Task* task);
    
    /**
    * Remove registration of a task in the timer manager.
    */
    void remove(Task* task);
    
    /**
     * For internal use only. You do not need to call this function.
     */
    void run();
  private:
    void testAndCall(Task* task);
    Task* _tasks = NULL;
};

extern SoftTimerClass SoftTimer;

#endif
