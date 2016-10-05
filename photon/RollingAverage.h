#ifndef rollingaverage
#define rollingaverage

#include "application.h"
#include <list>

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

#endif
