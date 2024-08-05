#include <Arduino.h>

const byte inputPin = 2;
const byte outputPin = 3;

volatile bool inputState = false;
volatile unsigned long lastHighTime;

void countPulses() {
  inputState = true;
  lastHighTime = millis();
}

void setup() {
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);

    // Set up external interrupt on PB2 (INT0)
    GIMSK |= (1 << INT0);  // Enable INT0
    MCUCR |= (1 << ISC01) | (1 << ISC00); // Trigger on rising edge

    lastHighTime = millis();
    sei(); // Enable global interrupts
}

ISR(INT0_vect) {
    inputState = true;
    lastHighTime = millis();
}

void loop() {
    unsigned long currentMillis = millis();

    if (inputState) {
        digitalWrite(outputPin, HIGH);
    }

    if (currentMillis - lastHighTime >= 10000) {
        // Reset output pin and input state
        digitalWrite(outputPin, LOW);
        inputState = false;
    }
}