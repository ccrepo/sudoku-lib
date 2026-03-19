#include <sstream>

#include "sudoku_clocks.h"

namespace cc {
namespace tools {
namespace sudoku {

const std::chrono::time_point<std::chrono::steady_clock> Clocks::_effective_epoch {
  std::chrono::steady_clock::now() };

int64_t Clocks::steady_clock_now_MS() {
  return std::chrono::duration_cast<std::chrono::milliseconds>
      ((std::chrono::steady_clock::now()) - _effective_epoch).count();
}

std::string Clocks::system_clock_as_string_sec() {

  thread_local static struct tm ts_struct;

  thread_local static std::ostringstream os;
  os.str("");

  std::time_t ts { std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) };
  localtime_r(&ts, &ts_struct);
  os << std::put_time(&ts_struct, "%Y%m%d %H:%M:%S");
  return os.str();
}

std::string Clocks::system_clock_as_string_ms() {

  thread_local static struct tm ts_struct;

  thread_local static std::ostringstream os;
  os.str("");

  auto now(std::chrono::system_clock::now());
  std::time_t ts { std::chrono::system_clock::to_time_t(now) };
  localtime_r(&ts, &ts_struct);

  os << std::put_time(&ts_struct, "%Y%m%d %H:%M:%S")
			    << "."
			    << std::setfill('0')
			    << std::setw(3)
			    << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;

  return os.str();
}


}
}
}
