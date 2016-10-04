#include "application.h"
#include <algorithm>
#include <vector>

class Sonar {
    public:
    Sonar(std::vector<pin_t> triggerPin, std::vector<pin_t> echoPins);
    std::vector<uint> getCentimeters();

    private:
    std::vector<pin_t> m_triggerPins;
    std::vector<pin_t> m_echoPins;
};

Sonar::Sonar(std::vector<pin_t> triggerPins, std::vector<pin_t> echoPins) : m_triggerPins(triggerPins), m_echoPins(echoPins) {
    // pinMode(m_triggerPin, OUTPUT);
    // digitalWriteFast(m_triggerPin, LOW);
    for (uint i = 0; i < m_triggerPins.size(); ++i) {
        pinMode(m_triggerPins[i], OUTPUT);
        digitalWriteFast(m_triggerPins[i], LOW);
    }
    // pinMode(m_echoPin, INPUT);

    // std::for_each(std::begin(m_echoPins), std::end(m_echoPins), [](const pin_t & echoPin) {
    //     pinMode(echoPin, INPUT);
    // });
    for (uint i = 0; i < m_echoPins.size(); ++i) {
        Serial.printf("Setting pin as input: %2d\n", m_echoPins[i]);
        pinMode(m_echoPins[i], INPUT);
    }
    Serial.println("Ready!");
}

std::vector<uint> Sonar::getCentimeters() {
    Serial.println("Sonar::getCentimeters");
    Serial.println("10 micro seconds - strt");
    for (uint i = 0; i < m_triggerPins[i]; ++i) {
        digitalWriteFast(m_triggerPins[i], HIGH);
    }
    delayMicroseconds(10);
    for (uint i = 0; i < m_triggerPins[i]; ++i) {
        digitalWriteFast(m_triggerPins[i], LOW);
    }
    // digitalWriteFast(m_triggerPin, HIGH);
    // delayMicroseconds(10);
    // digitalWriteFast(m_triggerPin, LOW);
    Serial.println("10 micro seconds - fin");

    std::vector<uint> results;
    // std::transform(std::begin(m_echoPins), std::end(m_echoPins), std::back_inserter(results), [](const pin_t & echoPin) {
    //   return uint32_t(pulseIn(echoPin, HIGH) / 29 / 2);
    // });
    for (uint i = 0; i < m_echoPins.size(); ++i) {
        Serial.printf("Polling pin %2d ", m_echoPins[i]);
        uint raw = pulseIn(m_echoPins[i], HIGH);
        Serial.printf(" Raw data: %2d\n", raw);
        results.push_back(raw / 29 / 2);
    }
    Serial.println("Returning results");
    return results;
}

Sonar* sonar;

void setup() {
    Serial.begin(115200);
    std::vector<pin_t> triggerPins = { D2, D1 };
    std::vector<pin_t> echoPins = { D6, D5 };
    sonar = new Sonar(triggerPins, echoPins);
    // sonar = new Sonar(D2, { D6 });
    delay(50);
}

void loop() {
    // uint32_t cm(sonar->getCentimeters());
    // Serial.printf("%2d cm\n", cm);
    std::vector<uint> measurements = sonar->getCentimeters();
    for (uint i = 0; i < measurements.size(); ++i) {
        Serial.printf("%2d cm ", measurements[i]);
    }
    Serial.printf("\n");
    delay(100);
}
