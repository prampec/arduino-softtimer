# Frequently Asked Questions about SoftTimer #

### I'm new to C++ programming. Can you recommend me SoftTimer? ###

If you just want to start periodic jobs, you can do that easily with SoftTimer. Also take a look at the provided tools (e.g. blinker, debouncer), as they are also easy to use. See example codes!

Writing your own Task implementation needs C++ knowledge. The C++ has a quite ugly syntax to define classes, that is hard to understand for beginners. But you can always use my implementations (like the [BlinkTask.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/BlinkTask.h), [BlinkTask.cpp](http://code.google.com/p/arduino-softtimer/source/browse/trunk/BlinkTask.cpp)) as a template.


### Can I change the period of a Task? ###

Sure you can do that. Please take a look at the Task.h interface documentation:
[Task.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/Task.h)

So you can set the period with "setPeriodMs()" any time.


### Do I need to remove/add my Task after changing the period? ###

You do not need to do that, but calling the setPeriodMs() will not reset the existing state of the task.
I you have the restart the counting of the timer while changing the period, you need to do it by either setting the lastCallTimeMicros property of the task, or remove/add your task again.


### I have a question, where should I post it? ###

You can reach me in prampec+softtimer@gmail.com address.