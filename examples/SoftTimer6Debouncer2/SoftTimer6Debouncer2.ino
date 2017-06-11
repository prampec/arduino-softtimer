/**
 * Note, that this example WILL FAIL TO LINK with the Arduino IDE.
 * This problem occurs due to the automatic dependency collection of the Arduino,
 * as PciManager.cpp will be also linked to this build.
 * As a solution, you might try to mess around to tweak this automatism, or
 * (and I recommend this one) just skip this example.
**/
// -- Pin change interrupt
#include <avr/interrupt.h>
#include <SoftTimer.h>
#include <Debouncer.h>

#define INPUT_PIN 3

// -- Define method signatures.
void onPressed();
void onReleased(unsigned long pressTimespan);

Debouncer debouncer(INPUT_PIN, MODE_CLOSE_ON_PUSH, onPressed, onReleased);


void setup() {
  Serial.begin(9800);
  // -- Setup external pin change interrupt for the pin.
  setupInterrupts(INPUT_PIN);
  Serial.println("Ready.");
}


void setupInterrupts(byte pin) {
  // -- PCINT vector will be 0, 1 or 2 depending on the pin.
  // --  digitalPinToPCICRbit(pin) will calculate which one it is.
  volatile uint8_t* pcicr = digitalPinToPCICR(pin);
  *pcicr |= (1 << digitalPinToPCICRbit(pin));
  volatile uint8_t* pcmsk = digitalPinToPCMSK(pin);
  *pcmsk |= (1 << digitalPinToPCMSKbit(pin));
  interrupts();
}

// -- Note that from the following functions only one is necessary
// --  depending on the PCINT group.
ISR(PCINT0_vect){
  pinChanged();
}
ISR(PCINT1_vect){
  pinChanged();
}
ISR(PCINT2_vect){
  pinChanged();
}


void pinChanged() {
  debouncer.pciHandleInterrupt(-1);
  Serial.print(".");
}

void onPressed() {
  Serial.println("pressed");
}
void onReleased(unsigned long pressTimespan) {
  Serial.print(pressTimespan);
  Serial.println(" - released");
}
