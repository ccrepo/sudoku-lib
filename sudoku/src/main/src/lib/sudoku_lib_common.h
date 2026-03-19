#ifndef SUDOKU_LIB_COMMON_H
#define SUDOKU_LIB_COMMON_H

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace cc {
namespace tools {
namespace sudoku {

class Game;
class Move;
class WorkI;

namespace lib {

class Common final {

public:
  static bool check_parameters(const std::vector<const void*>& params);

  static void copy_n(uint8_t* destination,
      const char* source,
      uint32_t n);

  static inline bool is_char_signed() {
    return _is_char_signed;
  }

  static uint32_t setup_game(Game& game,
      const std::string& position,
      bool solved_position);

  static uint32_t setup_game(Game& game,
      const std::string& position) {
    return Common::setup_game(game, position, false);
  }

  static bool get_all_possible_moves(const Game& game,
      std::vector<Move>& possible_moves);

  static void transform_moves(const WorkI& work,
      std::vector<std::pair<uint16_t, uint16_t>>& results);

  static void transform_moves(const Game& game,
      std::vector<std::pair<uint16_t, uint16_t>>& results);

  static std::string get_worker_load_summary();

private:
  static const bool _is_char_signed;

private:
  Common() = delete;
};

}
}
}
}

#endif
