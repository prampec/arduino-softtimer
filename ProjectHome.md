SoftTimer enable a higher level Arduino programing, jet easy to use, and lightweight.
You often face with the problem that you need to do multiply tasks in the same time. In SoftTimer manner programmer creates Tasks that runs periodically.

When you use SoftTimer you do not implement the "loop" function of the Arduino. All your code will run event driven, all processes running asynchronous, no more blocking code (like delay()) is needed.

I also try to add some usefully tools to use SoftTimer out of the box (like blinker, pwm, debouncer, etc.)

Debouncer class requires the PciManager library.

# Documentation content #

  * [Quick-start guide](QuickStartGuide.md)
  * [Why use SoftTimer and how does it work? ](WhyHow.md)
  * [Detailed description of the provided features.](Features.md)
  * [FAQ](FAQ.md)
  * [ChangeLog](ChangeLog.md)