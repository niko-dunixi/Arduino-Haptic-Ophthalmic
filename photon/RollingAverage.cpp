#include "RollingAverage.h"
RollingAverage::RollingAverage(uint bufferSize) : m_bufferSize(bufferSize), m_total(0) {
    Serial.printf("Creating rolling average with: %2d / %2d\n", m_total, m_bufferSize);
}
void RollingAverage::addValue(uint value) {
    // NOTE: this should be fine as an "if" instead of a
    // "while", but there is a memory leak in here somewhere
    // and I'm coding defensively until I find it.
    while (hasAverage()) {
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
Ready.
