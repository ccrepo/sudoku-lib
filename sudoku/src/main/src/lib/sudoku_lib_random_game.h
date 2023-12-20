#ifndef SUDOKU_LIB_RANDOMGAME_H
#define SUDOKU_LIB_RANDOMGAME_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "sudoku_api.h"

#include "sudoku_lib_codes.h"

namespace cc {
namespace tools {
namespace sudoku {

namespace lib {

class RandomGame final {

public:
  RandomGame();

  ~RandomGame() {
  }

  uint32_t get_random_game(
      std::vector<std::pair<uint16_t, uint16_t>>& out_moves,
      int32_t& out_runtime);

private:
  static const std::string _start_position;

private:
  const std::string _request;

private:
  RandomGame(const RandomGame&) = delete;
  RandomGame operator=(const RandomGame&) = delete;

};


}
}
}
}

#endif
