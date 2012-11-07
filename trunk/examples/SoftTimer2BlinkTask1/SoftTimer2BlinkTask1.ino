#include <SoftTimer.h>
#include <BlinkTask.h>

#define LED_PIN 13

// -- On for 1000ms, off for the same time, and repeat it forever.
BlinkTask hartbeat(LED_PIN, 1000);

void setup() {
  hartbeat.start();
}

