#include "application.h"
#include <algorithm>
#include <vector>
#include <list>

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

class RollingAverage {
  public:
  RollingAverage(uint bufferSize);
  void addValue(uint value);
  bool hasAverage();
  uint getAverage();

  private:
  uint m_bufferSize;
  uint m_total;
  std::list<uint> m_values;
};

RollingAverage::RollingAverage(uint bufferSize) : m_bufferSize(bufferSize), m_total(0) {
    Serial.printf("Creating buffered average with size: %2d / %2d\n", m_total, m_bufferSize);
}

void RollingAverage::addValue(uint value) {
    if (hasAverage()) {
        uint front = m_values.front();
        m_values.pop_front();
        m_total -= front;
    }
    m_total += value;
    m_values.push_back(value);
}

bool RollingAverage::hasAverage() {
    return m_values.size() >= m_bufferSize;
}

uint RollingAverage::getAverage() {
    return m_total / m_bufferSize;
}

// TODO: Create a vector of pairs
std::vector<SonarSensor*> sensors;
std::vector<RollingAverage> avgs;

void setup() {
    Serial.begin(115200);
    // Serial.begin(9600);
    sensors.push_back(new SonarSensor(D2, D6));
    sensors.push_back(new SonarSensor(D1, D5));
    avgs.emplace_back(25);
    avgs.emplace_back(25);
    delay(50);
}

// Issue with trying to poll these devices sequentially.
// It has to be done in a specific way.
// For now it must be done this way, however, I think there
// should be a workaround.
// http://stackoverflow.com/questions/25823179/driving-two-ultrasonic-sensor-with-arduino#comment40397990_25823179
void loop() {
    for (uint i = 0; i < sensors.size(); ++i) {
        uint cm = sensors[i]->getCM();
        avgs[i].addValue(cm);
        // Serial.printf("%2d cm ", cm);
        if (avgs[i].hasAverage()) {
            uint avg = avgs[i].getAverage();
            Serial.printf("(avg %2d cm) ", avgs[i].getAverage());
        }
        delay(75);
    }
    Serial.println();
}
