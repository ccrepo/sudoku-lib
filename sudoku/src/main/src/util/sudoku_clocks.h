#ifndef SUDOKU_CLOCKS_H
#define SUDOKU_CLOCKS_H

#include <ctime>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std::chrono_literals;

namespace cc {
namespace tools {
namespace sudoku {

class Clocks final {

public:
  static int64_t steady_clock_now_MS();

  static std::string system_clock_as_string_ms();

  static std::string system_clock_as_string_sec();

private:
  Clocks() = delete;

private:
  static const std::chrono::time_point<std::chrono::steady_clock> _effective_epoch;

};

}
}
}

#endif
