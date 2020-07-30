/*
  Handle Sticks Torch Timer
  Combines the two LeTorch buttons in to one physical button that triggers the Ignitor for a specified time once gas is opened.

  July 2020 by Simon Cleveland J&M Special Effects
*/
#include <Arduino.h>
#define BUTTONPIN 3    // the number of the pushbutton pin
#define OUTPUTPIN 12      // the number of the LED pin

// Variables will change:
int outputState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonReading = HIGH;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long maxButtonHoldTimmer = 500; //
unsigned long lastButtonStateChange = 0;

void setup() {
  pinMode(BUTTONPIN, INPUT_PULLUP);
  pinMode(OUTPUTPIN, OUTPUT);

  // set initial LED state
  digitalWrite(OUTPUTPIN, outputState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(BUTTONPIN);
  
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonReading) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      lastButtonStateChange = millis();  
    }
  }
  
  if((buttonState == HIGH) || (millis() - lastButtonStateChange > maxButtonHoldTimmer)) {
    outputState = LOW;
  }
  else
  {
    outputState = HIGH;
  }

  
  // set the LED:
  digitalWrite(OUTPUTPIN, outputState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonReading = reading;
}