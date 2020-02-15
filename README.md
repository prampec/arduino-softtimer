# Arduino SoftTimer library [![Build Status](https://travis-ci.org/prampec/arduino-softtimer.svg?branch=master)](https://travis-ci.org/prampec/arduino-softtimer) #

## Note for v4.0 ##

**All PinChangeInterrupt based functionality was moved out from this core library to an external SoftTimer-Pci library. Please include that one as well if you depends on Debouncer or Rotary!**

## Description ##

With SoftTimer you can reach a higher Arduino programing level, yet it is easy to use, and lightweight.

You often face with the problem that you need to do multiply tasks in the same time. When using SoftTimer, programmer organizes the business logic into Tasks, and the timer manager of SoftTimer takes care about the exact timing of the tasks.

When you use SoftTimer you do not implement the "loop" function of the Arduino. All your code will run *event driven*, all processes running asynchronous, no more blocking code (like delay()) is to be used.

I also try to add some usefully tools to use SoftTimer out of the box (like blinker, pwm, tone-player etc.)

You can install SoftTimer library directly from the Library Manager of the Arduino IDE. Follow this link for details: [How to Install a Library](https://www.arduino.cc/en/Guide/Libraries#toc3)

The detailed documentation can be found here:

# [Link to Documentation](https://github.com/prampec/arduino-softtimer/blob/wiki/SoftTimer.md) #
