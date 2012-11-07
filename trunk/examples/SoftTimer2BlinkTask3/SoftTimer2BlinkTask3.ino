#include <SoftTimer.h>
#include <BlinkTask.h>

#define LED_PIN 13

// -- On for 300ms off for 200ms, repeat it 3 times, than stop.
BlinkTask hartbeat(LED_PIN, 300, 200, 3);

void setup() {
  hartbeat.start();
}

