/**
 * File: HardDimmer.h
 * Description:
 * SoftTimer library is a lightweight but effective event based timeshare solution for Arduino.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2020 Balazs Kelemen
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

#ifndef HARDDIMMER_H
#define HARDDIMMER_H

#include "Task.h"
#include "SoftPwmTask.h"
#include "Arduino.h"

#define DIMMER_DIRECTION_HIGH 1
#define DIMMER_DIRECTION_LOW -1

#define DEFAULT_STEP_COUNT 8

/**
 * HardDimmer should be a drop in replacement for Dimmer,
 * expect for the constructor.
 */
class HardDimmer : public Task
{
  public:
    /**
     * We use the SoftPwmTask for dimming.
     *  pwm - The predefined SoftPwm task.
     *  frequencyMs - Milliseconds will be passed in the OFF->ON->OFF cycle.
     */
    HardDimmer(int pwmPin, int frequencyMs);
   
    /**
     * Start an unlimited pulsation from the current value on, in the current direction.
     */
    void startPulsate();
    
    /**
     * Hold current PWM value on the output.
     */
    void hold();
    
    /**
     * Stop PWM, and set output to LOW.
     */
    void off();
    
    /**
     * Make the dimming to change direction.
     */
    void revertDirection();
   
    /**
     * Milliseconds will be passed in the OFF->ON->OFF cycle.
     */
    void setFrequency(int frequencyMs);
    
    /**
     * Get the upper level of the pwm.
     */
    byte getUpperLimit();
    
    void setBottomLevel(byte value = 0) 
    {
      this->_bottomLevel = value;
    }
    void setTopLevel(byte value = 255) 
    {
      this->_topLevel = value;
    }
   
    /**
     * Current dim level PWM value. Note that the value should be between bottomLevel and topLevel.
     */
    float value;
    
    /**
     * Stop if zero, or pwm->upperLimit is reached.
     */
    bool stopOnLimit;
     
    /**
     * Can be one of DIMMER_DIRECTION_HIGH or DIMMER_DIRECTION_LOW.
     */
    char direction;
    
    /**
     * Level-arranging steps should be performed within each full OFF->ON change. Will be applied if setFrequency() is called.
     */
    byte stepCount;
     
  private:
    int _pwmPin;
    float _stepLevel;
    static void step(Task* me);
    float _topLevel = 255;
    float _bottomLevel = 0;
};

#endif

