#include <SoftTimer.h>
#include <DelayRun.h>

#define OUT_PIN 13

// -- Define method signatures.
boolean turnOff(Task* task);
boolean turnOn(Task* task);

// -- This task will turn off the LED after 1 second.
DelayRun offTask(1000, turnOff);
// -- This task will turn on the LED after 2 seconds.
// -- After the onTask we loop the offTask.
DelayRun onTask(2000, turnOn, &offTask);


void setup() {
  // -- We close the loop, so after offTask the onTask will start.
  offTask.followedBy = &onTask;

  pinMode(OUT_PIN, OUTPUT);
  
  // -- Turn on the LED;
  digitalWrite(OUT_PIN, HIGH);
  
  // -- Start the offTask to take effect after 1 second.
  offTask.startDelayed();
  
}

boolean turnOff(Task* task) {
  digitalWrite(OUT_PIN, LOW);
  return true; // -- Return true to enable the "followedBy" task.
}
boolean turnOn(Task* task) {
  digitalWrite(OUT_PIN, HIGH);
  return true; // -- Return true to enable the "followedBy" task.
}

