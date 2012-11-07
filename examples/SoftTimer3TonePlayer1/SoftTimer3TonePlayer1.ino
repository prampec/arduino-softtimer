#include <SoftTimer.h>
#include <TonePlayer.h>

#define BEEPER_PIN  10

// -- Player initialized with 200ms as base time-span.
TonePlayer tonePlayer(BEEPER_PIN, 200);

void setup(void)
{
  tonePlayer.play("c1g1c1g1j2j2c1g1c1g1j2j2o1n1l1j1h2l2_2j1h1g1e1c2c2");
}

