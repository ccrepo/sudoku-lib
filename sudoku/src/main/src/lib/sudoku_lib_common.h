#ifndef SUDOKU_LIB_COMMON_H
#define SUDOKU_LIB_COMMON_H

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>

namespace cc {
namespace tools {
namespace sudoku {

class Game;
class Move;
class WorkI;

namespace lib {

class Common final {

public:
  static bool check_parameters(const char* request,
      uint8_t* response,
      int32_t* runtime);

  static void copy_n(uint8_t* destination,
      const char* source,
      uint32_t n);

  static inline bool is_char_signed() {
    return _is_char_signed;
  }

  static uint32_t setup_board(Game& game,
      const std::string& position);

  static bool get_all_possible_moves(const Game& game,
      std::vector<Move>& possible_moves);

  static void transform_moves(const std::shared_ptr<WorkI>& work,
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
