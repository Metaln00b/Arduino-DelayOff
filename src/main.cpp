#include <Arduino.h>

const byte inputPin = 1;  // PB1 auf dem ATtiny85
const byte outputPin = 2; // PB2 auf dem ATtiny85

unsigned long delayOff = 45000;
unsigned long lastHighTime;

void setup() {
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);

    digitalWrite(outputPin, LOW);  // Ensure output pin starts LOW
    lastHighTime = millis();
}

void loop() {
    unsigned long currentMillis = millis();
    bool currentInputState = digitalRead(inputPin);

    if (currentInputState == HIGH) {
        lastHighTime = currentMillis;
        digitalWrite(outputPin, HIGH);
    }

    if (currentMillis - lastHighTime >= delayOff) {
        digitalWrite(outputPin, LOW);
    }
}