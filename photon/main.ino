#include "application.h"
#include <algorithm>
#include <vector>

// http://www.micropik.com/PDF/HCSR04.pdf

class Sonar {
    public:
    Sonar(std::vector<pin_t> triggerPin, std::vector<pin_t> echoPins);
    std::vector<uint> getCentimeters();

    private:
    std::vector<pin_t> m_triggerPins;
    std::vector<pin_t> m_echoPins;
};

Sonar::Sonar(std::vector<pin_t> triggerPins, std::vector<pin_t> echoPins) : m_triggerPins(triggerPins), m_echoPins(echoPins) {
    for (uint i = 0; i < m_triggerPins.size(); ++i) {
        pinMode(m_triggerPins[i], OUTPUT);
        digitalWriteFast(m_triggerPins[i], LOW);
    }
    for (uint i = 0; i < m_echoPins.size(); ++i) {
        Serial.printf("Setting pin as input: %2d\n", m_echoPins[i]);
        pinMode(m_echoPins[i], INPUT);
    }
    Serial.println("Ready!");
}

std::vector<uint> Sonar::getCentimeters() {
    // Issue with trying to poll these devices sequentially.
    // It has to be done in a specific way.
    // For now it must be done this way, however, I think there
    // should be a workaround.
    // http://stackoverflow.com/questions/25823179/driving-two-ultrasonic-sensor-with-arduino#comment40397990_25823179

    std::vector<uint> results;
    for (uint i = 0; i < m_triggerPins.size(); ++i) {
        // Start ping
        digitalWrite(m_triggerPins[i], HIGH);
        delayMicroseconds(10);
        digitalWrite(m_triggerPins[i], LOW);
        // Get result
        uint raw = pulseIn(m_echoPins[i], HIGH);
        results.push_back(raw / 29 / 2); // TODO: verify this equation... I lost the link where I originally found it. I don't think it's actually correct.
        delay(75);
    }
    return results;

    // // Serial.println("Sonar::getCentimeters");
    // // Serial.println("10 micro seconds - strt");
    // for (uint i = 0; i < m_triggerPins[i]; ++i) {
    //     digitalWriteFast(m_triggerPins[i], HIGH);
    // }
    // delayMicroseconds(10);
    // for (uint i = 0; i < m_triggerPins[i]; ++i) {
    //     digitalWriteFast(m_triggerPins[i], LOW);
    // }
    // // Serial.println("10 micro seconds - fin");

    // std::vector<uint> results;
    // for (uint i = 0; i < m_echoPins.size(); ++i) {
    //     Serial.printf("Polling pin %2d ", m_echoPins[i]);
    //     uint raw = pulseIn(m_echoPins[i], HIGH);
    //     Serial.printf(" Raw data: %2d\n", raw);
    //     results.push_back(raw / 29 / 2);
    //     delay(25);
    // }
    // Serial.println("Returning results");
    // return results;
}

Sonar* sonar;

void setup() {
    // Serial.begin(115200);
    Serial.begin(9600);
    std::vector<pin_t> triggerPins = { D1, D2 };
    std::vector<pin_t> echoPins = { D5, D6 };
    sonar = new Sonar(triggerPins, echoPins);
    delay(50);
}

void loop() {
    std::vector<uint> measurements = sonar->getCentimeters();
    for (uint i = 0; i < measurements.size(); ++i) {
        Serial.printf("%2d cm ", measurements[i]);
    }
    Serial.printf("\n");
    delay(100);
}
