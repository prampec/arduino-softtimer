# Introduction #

SoftTimer is an Arduino library.

SoftTimer enables a higher level Arduino programing, while its lightweight and easy to use.
The programmer is often faced with the problem that he/she needs to run multiple tasks at the same time. With SoftTimer, the programmer is able create Tasks that run periodically.

With SoftTimer, one does not implement the "loop" function of the Arduino. Instead, all code will be event driven, all processes running asynchronously, eliminating the need for any blocking code (like sleep).

Some useful tools are also included with SoftTimer out of the box (like blinker, pwm, debouncer, etc.)

You can download the actual version from the [Releases page](https://github.com/prampec/arduino-softtimer/releases).


# Documentation content #
  * [Quick-start guide](QuickStartGuide.md)
  * [Why use SoftTimer and how does it work? ](WhyHow.md)
  * [Detailed description of the provided features.](Features.md)
