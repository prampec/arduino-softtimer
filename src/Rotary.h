/**
 * File: Rotary.h
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

#ifndef ROTARY_H
#define ROTARY_H

#include <SoftTimer.h>
#include <PciListener.h>
#include <Arduino.h>
#include <PciListenerImp2.h>
#include <IPciChangeHandler.h>

#define DIRECTION_CW 1
#define DIRECTION_CCW -1

class Rotary : public Task, public IPciChangeHandler
{
  public:
    /**
      * Create a debouncing task with the following parameters.
      *  pin - Checking pin for input.
      *  pushMode - CLOSE_ON_PUSH / OPEN_ON_PUSH  - Your button are normally wired to be NO (Normally Openned), so USE CLOSE_ON_PUSH.
      *   But sometimes it is NC (Normally Closed), in this case use OPEN_ON_PUSH.
      *  onPressed() - A callback function pointer. This function is called when the bouncing button is really pushed. (Optional,
      *   pass NULL, if you do not want to use this feature.)
      *  onReleased(pressTimespan) - A callback function pointer. This function is called when the bouncing button is really
      *   released. (Optional, pass NULL, if you do not want to use this feature.)
      *   The callback receives the pressTimespan parameter that is the time in milliseconds the button was hold down before
      *   it was released.
      */
    Rotary(int pinA, int pinB, void (*onRotation)(short direction, Rotary* rotary), bool pullUp=false);
    
    /**
     * Please call this function on interrupt.
     */
    virtual void pciHandleChange(byte changedTo, PciListenerImp2* listener);

  private:
    PciListenerImp2 _listenerA = PciListenerImp2();
    PciListenerImp2 _listenerB = PciListenerImp2();
    volatile int _stateCW;
    volatile int _stateCCW;
    void (*_onRotation)(short direction, Rotary* rotary);
    static void step(Task* me);
};

#endif

