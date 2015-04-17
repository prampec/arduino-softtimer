# Quick-Start guide #

1. Include SoftTimer in your program.
```
#include <SoftTimer.h>
```

2. You need to create a Task with parameters of period (ms) and the callback function. E.g. callBack1 is to be called in every 2000 milliseconds (that is 2 seconds):
```
Task t1(2000, callBack1);

void callBack1(Task* me) {
  // -- my code comes here
}
```

3. Register your task to the SoftTimer (Timer Manager).
```
void setup() {
  SoftTimer.add(&t1);
}
```

4. You are finished. You may add more tasks, or use some bundled task implementations.

Full code:
```
#include <SoftTimer.h>

// -- taskOn will be launched on every 2 seconds.
Task taskOn(2000, turnOn);
// -- taskOff will be launched on every 1111 milliseconds.
Task taskOff(1111, turnOff);

void setup() {
  // -- Mark pin 13 as an output pin.
  pinMode(13, OUTPUT);

  // -- Register the tasks to the timer manager. Both tasks will start immediately.
  SoftTimer.add(&taskOn);
  SoftTimer.add(&taskOff);
}

/**
 * Turn ON Arduino's LED on pin 13.
 */
void turnOn(Task* me) {
  digitalWrite(13, HIGH);
}

/**
 * Turn OFF Arduino's LED on pin 13.
 */
void turnOff(Task* me) {
  digitalWrite(13, LOW);
}
```

Note, that the "loop()" method is absent form this full code. This is intended to be so!