/**
 * File: FrequencyTask.h
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

#ifndef FREQUENCYTASK_H
#define FREQUENCYTASK_H

#include "Task.h"
#include "DelayRun.h"
#include "Arduino.h"

class FrequencyTask : public Task
{
  public:
    /**
     * Initialize a frequency generator on the pin with the given initial frequency value.
     * Note, that you have to register the task to the timer manager to let it run.
     *  outPin - The digital pin of the output.
     *  freq - Initial frequency.
     */
    FrequencyTask(int outPin, float freq);
   
    void init() override;

    /**
     * Adjust the frequency.
     */
    void setFrequency(float freq);
    
  private:
    int _outPin;
    boolean _stateOn;
    uint8_t _bitMask;
#if defined(ESP8266) || defined(ARDUINO_ARCH_SAMD)
    volatile uint32_t *_portRegister;
#else
    volatile uint8_t *_portRegister;
#endif
    static void step(Task* me);
};

#endif

