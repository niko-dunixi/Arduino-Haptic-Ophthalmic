#include "application.h"
#include <algorithm>
#include <vector>

// http://www.micropik.com/PDF/HCSR04.pdf

class SonarSensor {
    public:
    SonarSensor(pin_t triggerPin, pin_t echoPins);
    uint getCM();

    private:
    pin_t m_triggerPin;
    pin_t m_echoPin;
};

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

std::vector<SonarSensor*> sensors;

void setup() {
    Serial.begin(115200);
    // Serial.begin(9600);
    sensors.push_back(new SonarSensor(D2, D6));
    sensors.push_back(new SonarSensor(D1, D5));
    delay(50);
}

// Issue with trying to poll these devices sequentially.
// It has to be done in a specific way.
// For now it must be done this way, however, I think there
// should be a workaround.
// http://stackoverflow.com/questions/25823179/driving-two-ultrasonic-sensor-with-arduino#comment40397990_25823179
void loop() {
    for (uint i = 0; i < sensors.size(); ++i) {
        Serial.printf("%2d cm ", sensors[i]->getCM());
        delay(75);
    }
    Serial.println();
}
