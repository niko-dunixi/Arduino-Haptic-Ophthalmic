#ifndef sonarsensor

#include "application.h"

class SonarSensor {
    public:
    SonarSensor(pin_t triggerPin, pin_t echoPins);
    uint getCM();

    private:
    pin_t m_triggerPin;
    pin_t m_echoPin;
};

#endif
