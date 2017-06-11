#include <SoftTimer.h>
#include <BlinkTask.h>

/**
 In this demo we assume that a switch is connected to digital pin 3,
 so an interrupt can be caught in channel 1.
*/

#define LED_PIN 13

// -- Define method signature.
void onPinEvent();

// -- On for 300ms off for 200ms, repeat it 3 times, than stop.
BlinkTask hartbeat(LED_PIN, 300, 200, 3);

void setup() {
  // -- Setup interrupt on pin 3 (which is channel 1).
  attachInterrupt(1, onPinEvent, CHANGE);
  // -- Blinks the LED 2 times on startup.
  hartbeat.start(2);
}

void onPinEvent() {
  // -- Blinks the LED 3 times after the interrupt.
  hartbeat.start(3);
}
