# Why use SoftTimer? #

You can add multitasking like functionalities for your code. For example you can blink a led while waiting for an input, or generate warning tones that does not block the running.
If you are facing with a more complex problem, you can organize your code in program tasks. You do not have to care about the timing of these tasks, while the Task Manager does this job for you. This way you can create simplified codes, that is easy to manage.

SoftTimer is a well designed object oriented solution, it is fun to work with.

SoftTimer has a small footprint, so using it will not mean a big memory penalty.



# How does it work? #


SoftTimer class is a Timer Manager that constantly scans the registered task if it is time to run it. If so (launch start time is passed) the callback is launched. No matter how long the callback is running, the next run will be scheduled according to the previous start time. The period of starting is defined at the Task. The period of the task may be changed if necessary.

Note that SoftTimer does not run tasks in the same time. The next task can be run after the currently running task is finished. When a callback runs longer than its period, the timing may fail. The tasks will be checked for run in the order of registration. You can register multiply tasks with a period of zero (0), the tasks will run after each other.
If you add only one task with a period value zero (0) it will act like original Arduino setup-loop methods.

```
#include <SoftTimer.h>

Task t1(0, myLoop);

void setup() {
  SoftTimer.add(&t1);
  // -- Put your setup code here, to run once.
}

void myLoop(Task* me) {
  // -- Put your main code here, to run repeatedly.
}
```

You can register (add) or remove tasks any time, and of course you can tune the timings later on.

Note that SoftTimer (from v2.0) works on **microsecond** basis. This means, you can not register task with period more than an hour!


# Options #

In SoftTimer.h there are some options provided. You can include/exclude the following macro definitions in the SoftTimer.h to enable/disable these options.

* __ENABLE_LOOP_ITERATION__ - With preventing loop() iteration you will benefit some milliseconds. On the other hand some platforms might depend on the loop(). If you are facing with strange behaviour, you might want to try including the ENABLE_LOOP_ITERATION option. ENABLE_LOOP_ITERATION is disabled by default.
* __STRICT_TIMING__ - By default the next start of a task scheduled from the begining of the previous execution. But executions might shift if an other task does not finish in time. With STRICT_TIMING the next execution is scheduled for the expected time. STRICT_TIMING is disabled by default, as it might likely to cause starvation in the Tasks.


# Platform dependent notes #

As SoftTimer eliminates the use of the "loop()" function, on platforms, that has some extra processing in every loop cicle, some troubles might appear.
As a workaround the ENABLE_LOOP_ITERATION option is introduced. (See Options above!)

For example, the internal watchdog in ESP8266 is normally feed by the system in every loop cycle. So you will have two options for ESP8266. Either include the ENABLE_LOOP_ITERATION option, or "feed" the watchdog manually to prevent resets. (Or just disable the watchdog.)
You can feed the watchdog with a task, e.g.:
```c
#include <SoftTimer.h>

// -- Define method signature.
void feedWatchdog(Task* me);

Task watchdogFeederTask(100, feedWatchdog);

void setup() {
  SoftTimer.add(&watchdogFeederTask);
}

void feedWatchdog(Task* me) {
  ESP.wdtFeed();
}
```
