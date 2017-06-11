// -- Pin change interrupt
#include <PciManager.h>
#include <SoftTimer.h>
#include <Debouncer.h>

#define INPUT_PIN 3

// -- Define method signatures.
void onPressed();
void onReleased(unsigned long pressTimespan);

Debouncer debouncer(INPUT_PIN, MODE_CLOSE_ON_PUSH, onPressed, onReleased);


void setup() {
  Serial.begin(9800);
  PciManager.registerListener(INPUT_PIN, &debouncer);
  Serial.println("Ready.");
}

void onPressed() {
  Serial.println("pressed");
}
void onReleased(unsigned long pressTimespan) {
  Serial.print(pressTimespan);
  Serial.println(" - released");
}
