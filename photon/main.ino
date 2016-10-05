#include "application.h"
#include <algorithm>
#include <vector>
#include <list>

#include "RollingAverage.h"
#include "SonarSensor.h"

// http://www.micropik.com/PDF/HCSR04.pdf

// TODO: Create a vector of pairs
std::vector<SonarSensor*> sensors;
std::vector<RollingAverage> avgs;

void setup() {
    Serial.begin(115200);
    // Serial.begin(9600);
    Serial.println("Setup::start");
    sensors.push_back(new SonarSensor(D2, D6));
    sensors.push_back(new SonarSensor(D1, D5));
    // avgs.emplace_back(25);
    // avgs.emplace_back(25);
    Serial.println("Setup::fin");
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
        Serial.printf("%2d cm ", cm);
        // avgs[i].addValue(cm);
        // if (avgs[i].hasAverage()) {
        //     uint avg = avgs[i].getAverage();
        //     Serial.printf("(avg %2d cm) ", avgs[i].getAverage());
        // }
        delay(75);
    }
    Serial.println();
}
