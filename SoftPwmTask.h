/**
 * File: SoftPwmTask.h
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

#ifndef SOFTPWMTASK_H
#define SOFTPWMTASK_H

#include "Task.h"
#include "Arduino.h"

class SoftPwmTask : public Task
{
  public:
    /**
     * We would like to do pwn on the given pin.
     */
    SoftPwmTask(int pin);
    
    /**
     * Just like in the Arduino implementation this method will set the duty level of the pin.
     *  value - The duty cycle: between 0 (always off (LOW)) and upperLimit (always on (HIGH)).
     */
    void analogWrite(byte value);
    
    /**
     * Turns the output to low.
     */
    void off();
    
    /**
     * The "always on" level of the PWM. The default is 255.
     */
    byte upperLimit;
	  
  private:
    int _outPin;
    byte _value;
    byte _counter;
    static void step(Task* me);
    
    uint8_t _bitMask;
    volatile uint8_t *_portRegister;
};

#endif
