#include <SoftTimer.h>
#include <SoftPwmTask.h>

#define OUT_PIN  13

// -- Set up PWM to the out pin.
SoftPwmTask pwm(OUT_PIN);

void setup(void)
{
  // -- Register the task in the timer manager.
  SoftTimer.add(&pwm);
  
  // -- Writes a value of 128. That means output will "dimmed" half way. 
  pwm.analogWrite(128);
}

