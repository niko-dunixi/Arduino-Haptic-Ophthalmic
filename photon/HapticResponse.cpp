#include "HapticResponse.h"

HapticResponse::HapticResponse(pin_t pin, uint maxValue) : m_pin(pin), m_maxValue(maxValue) {
  pinMode(m_pin, OUTPUT);
  Serial.printf("Using pin %2d and capping at %2d\n", m_pin, m_maxValue);
}

void HapticResponse::buzz(uint value) {
  // If the value is greater than m_maxValue
  // return. We just assume that the element
  // is too far away.
  if (value >= m_maxValue) {
    analogWrite(m_pin, 0);
    return;
  }
  float proportion = (float) (m_maxValue - value) / (float) (m_maxValue);
  float finalValue = (int) (proportion * 255);
  Serial.printf("Value %2d, Proportion %f, Final %f ", value, proportion, finalValue);
  analogWrite(m_pin, finalValue);
}
