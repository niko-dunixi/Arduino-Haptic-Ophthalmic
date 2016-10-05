// This #include statement was automatically added by the Particle IDE.
#include "HapticResponse.h"

#include "application.h"
#include <algorithm>
#include <vector>
#include <list>

#include "SonarSensor.h"
#include "RollingAverage.h"
#include "HapticResponse.h"

// http://www.micropik.com/PDF/HCSR04.pdf

// TODO: Create a vector of tuples
std::vector<SonarSensor*> sensors;
std::vector<RollingAverage> avgs;
std::vector<HapticResponse> resps;

void setup() {
    Serial.begin(115200);
    // Serial.begin(9600);
    Serial.println("Setup::start");
    sensors.push_back(new SonarSensor(D1, D5));
    sensors.push_back(new SonarSensor(D2, D6));
    // avgs.emplace_back(25);
    // avgs.emplace_back(25);
    resps.emplace_back(A4, 150);
    resps.emplace_back(A5, 150);
    Serial.println("Setup::fin");
    delay(50);
}

// Issue with trying to poll these devices sequentially.
// It has to be done in a specific way.
// For now it must be done this way, however, I think there
// should be a workaround.
// http://stackoverflow.com/questions/25823179/driving-two-ultrasonic-sensor-with-arduino#comment40397990_25823179

int loopCount = 0;

void loop() {
  int values[2];
  for (uint i = 0; i < sensors.size(); ++i) {
    uint cm = sensors[i]->getCM();
    values[i] = cm;
    Serial.printf("%2d cm ", cm);
    // avgs[i].addValue(cm);
    // if (avgs[i].hasAverage()) {
    //     uint avg = avgs[i].getAverage();
    //     Serial.printf("(avg %2d cm) ", avgs[i].getAverage());
    // }
    delay(75);
  }
  Serial.println();
  if (loopCount % 1 == 0) {
    for (uint i = 0; i < resps.size(); ++i) {
      resps[i].buzz(values[i]);
    }
    Serial.println();
  }
  ++loopCount;
}
