/**
 * File: TonePlayer.cpp
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

#include "TonePlayer.h"
#include "SoftTimer.h"

const float trot = 1.05946309435929; // -- The twelfth root of two
const float A440 = 440.0; // -- A440 (pitch standard)

TonePlayer::TonePlayer(int pin, unsigned long baseLength)  : Task(0, &(TonePlayer::step)) {
  _outPin = pin;
  _baseLength = baseLength;
}

void TonePlayer::play(String tones) {
  this->_tones = tones;

  SoftTimer.remove(this);
  this->setPeriodMs(0);
  this->_playing = true;
  this->_pos = 0;
  SoftTimer.add(this);
}

void TonePlayer::step(Task* task) {
  TonePlayer* tp = (TonePlayer*)task;
  
  // -- play a small silence after each tone
  if(tp->_playing) {
    tp->_playing = false;
    noTone(tp->_outPin);
    tp->setPeriodMs(tp->_baseLength / 20);
    return;
  }

  // -- finished
  if(tp->_pos >= tp->_tones.length()) {
    SoftTimer.remove(tp);
    noTone(tp->_outPin);
    return;
  }

  // -- calculate length
  char cLength = tp->_tones[tp->_pos+1];
  tp->setPeriodMs((unsigned long)(cLength-'0') * tp->_baseLength);

  // -- calculate tone
  char cPitch = tp->_tones[tp->_pos];
  if(cPitch == '_') {
    // -- add silence
    noTone(tp->_outPin);
  } else {
    float val = A440;
    int tune = (int)(cPitch-'j'); // -- 'j' character means A note
    if(tune < -9) {
      tune += 6; // -- Skip characters between character capital 'Z' and 'a'.
    }
    if(tune > 0) {
      while(tune != 0) {
        val *= trot;
        --tune;
      }
    } else {
      while(tune != 0) {
        val /= trot;
        ++tune;
      }
    }

    // -- play tone
    tone(tp->_outPin, val);
  }
  
  tp->_playing = true;
  tp->_pos += 2;
}

