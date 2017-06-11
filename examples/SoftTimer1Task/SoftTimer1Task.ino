#include <SoftTimer.h>

// -- Define method signature.
void callBack1(Task* me);
void callBack2(Task* me);

Task t1(2000, callBack1);
Task t2(1111, callBack2);

void setup() {
  pinMode(13, OUTPUT);
  SoftTimer.add(&t1);
  SoftTimer.add(&t2);
}

void callBack1(Task* me) {
  digitalWrite(13, HIGH);
}
void callBack2(Task* me) {
  digitalWrite(13, LOW);
}
