/**
 * File: TonePlayer.h
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

#ifndef TONEPLAYER_H
#define TONEPLAYER_H

#include "Arduino.h"
#include "Task.h"

class TonePlayer : Task
{
  public:

    /**
      * Initialize the player.
      *  pin - Speaker pin.
      *  baseLength - The minimal length of a tone will be played in milliseconds.
      */
    TonePlayer(int pin, unsigned long baseLength);

    /**
      * Play a series of tone.
      *  tones - Series of tones in the following form: A tone is described in two characters.
      *   First character is the note marker, second character is the length multiplier of the
      *   baseLength specified in the constructor. More pairs of tone can be specified after each
      *   other. Note marker is coded as follows:
      *   character 'j' means the tone 'A4'. Characters in alphabetic order will represent the
      *   musical notes. E.g. j, h, i means A, A#, B. Thus 'c' character will mean note 'C'.
      *
      *   A C   F H   K M O   R T   W Y a   d f   i k m   p r   u w y 
      *    B D E G I J L N P Q S U V X Z b c e g h j l n o q s t v x z
      *
      *   Character '_' means silence.
      *
      *   "c2e2g4" - Means C-note for 2 time-span, D-note for 2 time-span, E-note for 4 time-span.
      */
    void play(String tones);
  private:
    int _outPin;
    unsigned long _baseLength;
    String _tones;
    int _pos;
    bool _playing;
    static void step(Task* me);
};

#endif
