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

You can register (add) or remove tasks any time.

Note that SoftTimer (from v2.0) works on **microsecond** basis. This means, you can not register task with period more than an hour!