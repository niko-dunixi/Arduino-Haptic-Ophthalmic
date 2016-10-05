#include "SonarSensor.h"

SonarSensor::SonarSensor(pin_t triggerPin, pin_t echoPin) : m_triggerPin(triggerPin), m_echoPin(echoPin) {
    Serial.print("Initializing. ");
    pinMode(m_triggerPin, OUTPUT);
    digitalWrite(m_triggerPin, LOW);
    pinMode(m_echoPin, INPUT);
    Serial.printf("Trigger: %2d, Echo: %2d\n", m_triggerPin, m_echoPin);
}

uint SonarSensor::getCM() {
    // Trigger ping
    digitalWrite(m_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_triggerPin, LOW);
    // Get response
    uint raw = pulseIn(m_echoPin, HIGH);
    return raw / 29 / 2;
}
