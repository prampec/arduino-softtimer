# Arduino SoftTimer library [![Build Status](https://travis-ci.org/prampec/arduino-softtimer.svg?branch=master)](https://travis-ci.org/prampec/arduino-softtimer) #

## Description ##

With SoftTimer you can reach a higher Arduino programming level, yet it is easy to use, and lightweight.

You are often faced with the problem that you need to do multiple tasks in the same time. When using SoftTimer, programmer organizes the business logic into Tasks, and the timer manager of SoftTimer takes care about the exact timing of the tasks.

When you use SoftTimer you do not implement the "loop" function of the Arduino. All your code will run *event driven*, all processes running asynchronous, no more blocking code (like delay()) is to be used.

I also try to add some useful tools to use SoftTimer out of the box (like blinker, pwm, debouncer, rotary etc.)

You can install SoftTimer library directly from the Library Manager of the Arduino IDE. Follow this link for details: [How to Install a Library](https://www.arduino.cc/en/Guide/Libraries#toc3)

An **external dependency** PciManager library is required to compile the SoftTimer library. You can also install it from the Library Manager, as mentioned above. 

The detailed documentation can be found here:

# [Link to Documentation](https://github.com/prampec/arduino-softtimer/blob/wiki/SoftTimer.md) #
