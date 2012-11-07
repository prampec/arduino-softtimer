#include <SoftTimer.h>
#include <BlinkTask.h>

#define LED_PIN 13

// -- On for 200ms off for 100ms, repeat it 2 times, sleep for 2000 ms and than start again.
BlinkTask hartbeat(LED_PIN, 200, 100, 2, 2000);

void setup() {
  hartbeat.start();
}

