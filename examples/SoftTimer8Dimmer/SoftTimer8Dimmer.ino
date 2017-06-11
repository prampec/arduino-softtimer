// -- Pin change interrupt
#include <PciManager.h>
#include <SoftTimer.h>
#include <Debouncer.h>
#include <SoftPwmTask.h>
#include <Dimmer.h>

#define OUT_PIN  13
#define INPUT_PIN 3
#define ON_OFF_FREQ_MS 1500
#define TRESHOLD_MS 600

// -- Define method signatures.
void onPressed();
void onReleased(unsigned long pressTimespan);

// -- Button for input.
Debouncer debouncer(INPUT_PIN, MODE_CLOSE_ON_PUSH, onPressed, onReleased);
// -- Set up PWM to the out pin.
SoftPwmTask pwm(OUT_PIN);
Dimmer dimmer(&pwm, 1500);

void setup() {
  PciManager.registerListener(INPUT_PIN, &debouncer);
}

void onPressed() {
  dimmer.startPulsate();
}

void onReleased(unsigned long pressTimespan) {
  if(pressTimespan < TRESHOLD_MS) {
    // -- It was just a fast clik, so stop on 0 or upperLimit.
    dimmer.stopOnLimit = true;
  } else {
    // -- Stop immediatelly.
    dimmer.hold();
  }
}


