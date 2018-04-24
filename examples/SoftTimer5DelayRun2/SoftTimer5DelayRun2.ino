#include <PciManager.h>
#include <SoftTimer.h>
#include <Debouncer.h>
#include <DelayRun.h>

#define INPUT_PIN 3
#define OUTPUT_PIN LED_BUILTIN

// -- Define method signatures.
void onPinChanged();
// -- Define method signatures.
boolean turnOff(Task* task);

Debouncer debouncer(INPUT_PIN, MODE_CLOSE_ON_PUSH, onPinChanged, NULL);
// -- Runs after 2 seconds
DelayRun offTask(2000, turnOff);

void setup() {
  Serial.begin(9800);
  PciManager.registerListener(INPUT_PIN, &debouncer);
  pinMode(OUTPUT_PIN, OUTPUT);
  Serial.println("Ready.");
}

void onPinChanged() {
  Serial.println("Event occurred");
  digitalWrite(OUTPUT_PIN, HIGH);
  offTask.startDelayed();
}

boolean turnOff(Task* task) {
  Serial.println("Delay elapsed");
  digitalWrite(OUTPUT_PIN, LOW);
}
