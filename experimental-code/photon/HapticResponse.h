#ifndef hapticresponse
#define hapticresponse

#include "application.h"

class HapticResponse {
public:
  HapticResponse(pin_t pin, uint maxValue);
  void buzz(uint value);

private:
  pin_t m_pin;
  uint m_maxValue;
};

#endif
