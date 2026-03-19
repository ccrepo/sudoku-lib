#ifndef SUDOKU_LIB_POSSIBLE_MOVES_H
#define SUDOKU_LIB_POSSIBLE_MOVES_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "sudoku_api.h"

#include "sudoku_lib_codes.h"

namespace cc {
namespace tools {
namespace sudoku {

class Router;

namespace lib {

class PossibleMoves final {

public:
  PossibleMoves(const std::string& request);

  ~PossibleMoves() {
  }

  uint32_t get_sudoku_possible_moves(
      std::vector<std::pair<uint16_t, uint16_t>>& out_moves,
      int32_t& out_runtime);

private:
  const std::string _request;
  const std::weak_ptr<Router> _router;

private:
  PossibleMoves(const PossibleMoves&) = delete;
  PossibleMoves operator=(const PossibleMoves&) = delete;

private:
  static constexpr uint16_t C_POSSIBLE_MOVES_BATCH_SIZE { 10 };
};

}
}
}
}

#endif
