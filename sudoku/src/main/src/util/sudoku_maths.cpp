#include <random>
#include <cassert>

#include "sudoku_maths.h"
#include "sudoku_durations.h"
#include "sudoku_worker.h"

namespace cc {
namespace tools {
namespace sudoku {

uint32_t Maths::get_short_rand_in_range() {

  return rand_in_range(Durations::C_DURATIONS_MINISCULE,
      Durations::C_DURATIONS_SHORTEST);
}

uint32_t Maths::rand_in_range(uint32_t low, uint32_t high) {

  thread_local static std::random_device device;

  thread_local static std::mt19937 generator(device());

  if (high <= low) {
    assert(!"upper is not more than lower");
  }

  std::uniform_int_distribution<> distr(low, high);

  return distr(generator);
}

}
}
}
