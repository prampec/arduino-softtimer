# Arduino SoftTimer library [![Build Status](https://travis-ci.org/prampec/arduino-softtimer.svg?branch=master)](https://travis-ci.org/prampec/arduino-softtimer) #

## Description ##

With SoftTimer you can reach a higher Arduino programming level, yet it is easy to use, and lightweight.

You are often faced with the problem that you need to do multiple tasks in the same time. When using SoftTimer, programmer organizes the business logic into Tasks, and the timer manager of SoftTimer takes care about the exact timing of the tasks.

When you use SoftTimer you do not implement the "loop" function of the Arduino. All your code will run *event driven*, all processes running asynchronous, no more blocking code (like delay()) is to be used.

I also try to add some useful tools to use SoftTimer out of the box (like blinker, pwm, debouncer, rotary etc.)

You can install SoftTimer library directly from the Library Manager of the Arduino IDE. Follow this link for details: [How to Install a Library](https://www.arduino.cc/en/Guide/Libraries#toc3)

## Non-AVR, Non-8bit Microcontroller Note ##

If you are using an MCU other than 8bit AVR, you should start with branch [NoPci](https://github.com/prampec/arduino-softtimer/commits/NoPci).

Details: SoftTimer is core timer system, but it also provides some usefull tools as mentioned above. Now, it turns out, that these tools are using features that are not compatible with other microcontrollers (e.g. pin change interrupt). Branch NoPci is clean from these tools, containing only those ones, which are likely to be compatible.

You can use this branch, by downloading a zip from it, and extract the content into your library folder, or if you are using platformIO, mark the branch in the lib_deps like so:
```
lib_deps=
  https://github.com/prampec/arduino-softtimer.git#NoPci
```

## External dependencies ##

An external dependency _PciManager_ library is required to compile the SoftTimer library. You can also install it from the Library Manager, as mentioned above. 

This external dependency can be eliminated, when using branch [NoPci](https://github.com/prampec/arduino-softtimer/commits/NoPci), as described above.

## Where to go from here? ##

The detailed documentation can be found here:

**[Link to Documentation](https://github.com/prampec/arduino-softtimer/blob/wiki/SoftTimer.md)**
