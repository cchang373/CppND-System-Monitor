#include "format.h"
#include <iomanip>
#include <string>

using std::string;
using std::to_string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds [[maybe_unused]]) {
  int h, m, s;
  h = seconds / 3600;
  m = (seconds % 3600) / 60;
  s = seconds - 3600 * h - 60 * m;

  std::ostringstream time;
  time << std::setw(2) << std::setfill('0') << h << ":" << std::setw(2)
       << std::setfill('0') << m << ":" << std::setw(2) << std::setfill('0')
       << s;
  return time.str();
}