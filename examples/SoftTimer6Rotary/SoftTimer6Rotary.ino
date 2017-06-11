#include <PciManager.h>
#include <Debouncer.h>
#include <Rotary.h>

#define ROT_PIN_A A4
#define ROT_PIN_B A5
#define ROT_PUSH A3

// -- Define method signatures.
void onRotate(short direction, Rotary* rotary);
void onRotPushPress();
void onRotPushRelease(unsigned long pressTime);

Rotary r(ROT_PIN_A, ROT_PIN_B, onRotate, true);
Debouncer rotPushDebouncer(ROT_PUSH, MODE_CLOSE_ON_PUSH, onRotPushPress, onRotPushRelease, true);

void setup() {
  Serial.begin(9600);
  PciManager.registerListener(ROT_PUSH, &rotPushDebouncer);

  Serial.println("Ready.");
}

void onRotate(short direction, Rotary* rotary) {
  if(direction == DIRECTION_CW) {
    Serial.println("cw");
  }
  if(direction == DIRECTION_CCW) {
    Serial.println("ccw");
  }
}

void onRotPushPress() {
  Serial.println("pushed");
}
void onRotPushRelease(unsigned long pressTime) {
  Serial.println("released");
}

