#include <SoftTimer.h>
#include <BlinkTask.h>
#include <TonePlayer.h>

/**
 In this demo we assume that a switch is connected to digital pin 3,
 so an interrupt can be caught in channel 1.
*/

#define BEEPER_PIN  10
#define LED_PIN     13

BlinkTask hartbeat(LED_PIN, 200, 100, 2, 2000);
// -- Player initialized with 200ms as base time-span.
TonePlayer tonePlayer(BEEPER_PIN, 200);

// -- Define method signature.
void onInfraEvent();

void setup(void)
{
  // -- Setup interrupt on pin 3 (which is channel 1).
  attachInterrupt(1, onInfraEvent, CHANGE);
  hartbeat.start();
  
  // -- Plays a welcome melody.
  tonePlayer.play("e1f1h2h1m2h2");
}

void onInfraEvent() {
  // -- Blinks the LED 3 times after the interrupt.
  tonePlayer.play("c1g1_2g1c1");
}
