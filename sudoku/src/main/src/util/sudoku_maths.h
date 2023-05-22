#ifndef SUDOKU_MATHS_H
#define SUDOKU_MATHS_H

namespace cc {
namespace tools {
namespace sudoku {

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

  static uint32_t rand_in_range(uint32_t low, uint32_t high);

  static uint32_t get_short_rand_in_range();

private:
  Maths() = delete;
};

}
}
}

#endif
