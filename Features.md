# Detailed description of the provided features #


## [BlinkTask](http://code.google.com/p/arduino-softtimer/source/browse/trunk/BlinkTask.h) ##


Every physical computing project starts with a blinking of a led.
You often need to have an indicator that shows the state of your program.

BlinkTask works in two mode:
  * Perpetual mode - Blinks forever.
  * Count mode - Blinks for an amount of occasion.

Perpetual mode has two kinds:
  * On-Off repetition - Repeat on and off states.
  * After a count of "on" times suspend for some time.

BlinkTask can work with on level of HIGH (default) or LOW.

Use start() function to register the task in the Timer Manager, so start blinking. See [BlinkTask.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/BlinkTask.h) header file for details.

```
#include <SoftTimer.h>
#include <BlinkTask.h>

#define LED_PIN 13

// -- On for 200ms off for 100ms, repeat it 2 times, sleep for 2000 ms and than start again.
BlinkTask heartbeat(LED_PIN, 200, 100, 2, 2000);

void setup() {
  heartbeat.start();
}
```



## [TonePlayer](http://code.google.com/p/arduino-softtimer/source/browse/trunk/TonePlayer.h) ##


Tone player plays a melody on a specified output pin using the tone() and noTone() Arduino functions. You can specify the melody in quite tricky way, see [TonePlayer.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/TonePlayer.h) header file for details.

```
#include <SoftTimer.h>
#include <TonePlayer.h>

#define BEEPER_PIN  10

TonePlayer tonePlayer(BEEPER_PIN, 200); // -- Tone manager

void setup(void)
{
  tonePlayer.play("c1g1c1g1j2j2c1g1c1g1j2j2o1n1l1j1h2l2_2j1h1g1e1c2c2");
}
```

Note, that you must take care to wait for the melody to finish before playing the next melody. Otherwise the next play will abort the previous melody. You may find the DelayRun task interesting.



## [SoftPwmTask](http://code.google.com/p/arduino-softtimer/source/browse/trunk/SoftPwmTask.h) ##

With this task you can add PWM functionality for pins that did not have hardware PWM. See [SoftPwmTask.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/SoftPwmTask.h) header file for details.

```
#include <SoftTimer.h>
#include <SoftPwmTask.h>

#define OUT_PIN  13

// -- Set up PWM to the out pin.
SoftPwmTask pwm(OUT_PIN);

void setup(void)
{
  // -- Register the task in the timer manager.
  SoftTimer.add(&pwm);
  
  // -- Writes a value of 128. That means output will "dimmed" half way. 
  pwm.analogWrite(128);
}
```


## [DelayRun](http://code.google.com/p/arduino-softtimer/source/browse/trunk/DelayRun.h) ##

This class is to launch something after an amount of period. You can even specify a "followedBy" task, which will be run after this one has finished. See [DelayRun.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/DelayRun.h) header file for details.

```
#include <SoftTimer.h>
#include <DelayRun.h>

#define OUT_PIN 13

// -- This task will turn off the LED after 1 second.
DelayRun offTask(1000, turnOff);
// -- This task will turn on the LED after 2 seconds.
// -- After the onTask we loop the offTask.
DelayRun onTask(2000, turnOn, &offTask);


void setup() {
  // -- We close the loop, so after offTask the onTask will start.
  offTask.followedBy = &onTask;

  pinMode(OUT_PIN, OUTPUT);
  
  // -- Turn on the LED;
  digitalWrite(OUT_PIN, HIGH);
  
  // -- Start the offTask to take effect after 1 second.
  offTask.startDelayed();
  
}

boolean turnOff(Task* task) {
  digitalWrite(OUT_PIN, LOW);
  return true; // -- Return true to enable the "followedBy" task.
}
boolean turnOn(Task* task) {
  digitalWrite(OUT_PIN, HIGH);
  return true; // -- Return true to enable the "followedBy" task.
}

```



## [Debouncer](http://code.google.com/p/arduino-softtimer/source/browse/trunk/Debouncer.h) ##


The debouncer task recommends to use the PciManager to manage the pin change interrupts. However you may handle interrupts manually.
After creating the debouncer task, you do not need to register it to the Timer Manager.

If you are using the PciManager, you only have to register the debouncer to the PciManager.

If you would like to handle PCI manually, you need make the pciHandleInterrupt() function to be called on pin change.

Debouncer will call your "onPressed" callback function when the button has a sable pressed state, and the "onReleased" on the end of the press. The "onReleased" callback also receive the total time passed on the pressing state.

You can use this debouncer both on Normally Opened and on Normally Closed circuits.

See [Debouncer.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/Debouncer.h) header file for details.

```
// -- Pin change interrupt
#include <PciManager.h>
#include <SoftTimer.h>
#include <Debouncer.h>

#define INPUT_PIN 3

Debouncer debouncer(INPUT_PIN, MODE_CLOSE_ON_PUSH, onPressed, onReleased);


void setup() {
  Serial.begin(9800);
  PciManager.registerListener(INPUT_PIN, &debouncer);
  Serial.println("Ready.");
}

void onPressed() {
  Serial.println("pressed");
}
void onReleased(unsigned long pressTimespanMs) {
  Serial.print("Released after (Ms): ");
  Serial.println(pressTimespanMs);
}
```





## [Heartbeat](http://code.google.com/p/arduino-softtimer/source/browse/trunk/Heartbeat.h) ##


Heartbeat is a special blinker. It is intended to use a visual indicator for your project more easy.

Heartbeat creates a custom timed BlinkTask and starts is immediately.

See [Heartbeat.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/Heartbeat.h) header file for details.




## [Dimmer](http://code.google.com/p/arduino-softtimer/source/browse/trunk/Dimmer.h) ##


With the dimmer you can easily adjust the PWM level of an output. The dimming is done in linear scale. Dimmer has some neat options, like hold/continue dimming, or revert direction any time. You can also set it up to be automatically stopped when limit (totally on/totally off) reached.

See [Dimmer.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/Dimmer.h) header file for details.



## [FrequencyTask](http://code.google.com/p/arduino-softtimer/source/browse/trunk/FrequencyTask.h) ##


Frequency task is just to play with the possibilities of the SoftTimer library. With the FrequencyTask you can generate square wave frequencies.

See [FrequencyTask.h](http://code.google.com/p/arduino-softtimer/source/browse/trunk/FrequencyTask.h) header file for details.