#include <SoftTimer.h>
#include <SoftPwmTask.h>

/* In this demonstration a pulsating is implemented. */

#define OUT_PIN  13

// -- Define method signatures.
void increment(Task* me);
void decrement(Task* me);

// -- Set up PWM to the out pin.
SoftPwmTask pwm(OUT_PIN);
// -- This task will increment the PWM value. Will be called in every 50 milliseconds.
Task incrementTask(40, increment);
// -- This task will decrement the PWM value. Will be called in every 25 milliseconds.
Task decrementTask(20, decrement);

byte value = 0;

void setup(void)
{
  // -- Register the PWM.
  pwm.analogWrite(value);
  SoftTimer.add(&pwm);
  
  // -- Register the increment task.
  SoftTimer.add(&incrementTask);
}

void increment(Task* me) {
  pwm.analogWrite(value);
  value += 16;
  if(value == 0) {
    // -- Byte value overflows: 240 + 16 = 0
    SoftTimer.remove(&incrementTask);
    SoftTimer.add(&decrementTask);
  }
}


void decrement(Task* me) {
  value -= 16;
  pwm.analogWrite(value);
  if(value == 0) {
    // -- Floor reached.
    SoftTimer.remove(&decrementTask);
    SoftTimer.add(&incrementTask);
  }
}

