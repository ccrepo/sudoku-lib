#ifndef SUDOKU_MATHS_H
#define SUDOKU_MATHS_H

#include <random>
#include <string>
#include <cassert>

#include "sudoku_durations.h"

namespace cc {
namespace tools {
namespace sudoku {

namespace logger {
extern thread_local const std::string thread_name;
}

class Maths final {

public:
  template<typename T, typename U>
  static inline T min(const T a, const U b) {
    return (a < b) ? a : b;
  }

  template<typename T, typename U>
  static inline T max(const T a, const U b) {
    return (a > b) ? a : b;
  }

  static inline uint32_t rand_in_range(uint32_t low, uint32_t high) {
    if (low > high) {
      assert(!"upper is not more than lower");
    }

    return (std::uniform_int_distribution<>(low, high)).operator()(_generator);
  }

  static inline uint32_t get_short_rand_in_range() {
    return rand_in_range(Durations::C_DURATIONS_MINISCULE,
        Durations::C_DURATIONS_SHORTEST);
  }

private:
  thread_local static std::random_device _device;

  thread_local static std::mt19937 _generator;

private:
  Maths() = delete;
};

}
}
}

#endif
