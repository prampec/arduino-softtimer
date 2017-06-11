#include <SoftTimer.h>
#include <Heartbeat.h>

#define LED_PIN 13

// -- Creates an starts a visible indicator.
Heartbeat heartbeat(LED_PIN);

// -- Define method signature.
void myLoop(Task* me);

// -- My task.
Task t1(0, myLoop);

void setup() {
  SoftTimer.add(&t1);
  // -- Put your setup code here, to run once.
}

void myLoop(Task* me) {
  // -- Put your main code here, to run repeatedly.
}
