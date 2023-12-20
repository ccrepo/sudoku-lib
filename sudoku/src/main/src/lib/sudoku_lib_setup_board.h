#ifndef SUDOKU_LIB_SETUPBOARD_H
#define SUDOKU_LIB_SETUPBOARD_H

#include <array>
#include <cstdint>
#include <string>

#include "sudoku_board.h"
#include "sudoku_geometry.h"
#include "sudoku_mask.h"
#include "sudoku_maths.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

class SetupBoard final : private Board {

public:
  SetupBoard(const Board& board);

  virtual ~SetupBoard() override {
  }

public:
  bool do_setup();

public:
  inline uint16_t generate_remove_limit() const {
    return Maths::rand_in_range(C_BOARDSTATE_REMOVELIMIT_MIN,
        C_BOARDSTATE_REMOVELIMIT_MAX);
  }

  inline uint16_t generate_shuffle_limit() const {
    return Maths::rand_in_range(C_BOARDSTATE_SHUFFLELIMIT_MIN,
        C_BOARDSTATE_SHUFFLELIMIT_MAX);
  }

  inline uint16_t get_remove_limit() const {
    return _remove_limit;
  }

  inline uint16_t get_shuffle_limit() const {
    return _shuffle_limit;
  }

  inline uint16_t get_remove_count() const {
    return _remove_count;
  }

  inline uint16_t get_shuffle_count() const {
    return _shuffle_count;
  }

public:
  inline Geometry::E_ROW_OR_COL get_rand_row_or_col() const {
    return static_cast<Geometry::E_ROW_OR_COL>(Maths::rand_in_range(0, 1));
  }

  inline uint16_t get_rand_block() const {
    return static_cast<uint16_t>(Maths::rand_in_range(0, Geometry::C_GEOMETRY_TOTAL_BLOCKS));
  }

public:
  inline bool is_valid() const {
    return _valid;
  }

public:
  std::string to_string() const;

private:
  std::array<Mask, Geometry::C_GEOMETRY_TOTAL_CELLS> _masks;

  std::array<int32_t, Geometry::C_GEOMETRY_TOTAL_CELLS> _indexes;

  const uint16_t _remove_limit;

  const uint16_t _shuffle_limit;

  uint16_t _remove_count;

  uint16_t _shuffle_count;

  bool _valid;

private:
  int32_t value_index_to_mask_index(uint16_t value_index) const;

  std::string mask_index_to_string(int32_t mask_index) const;

  inline bool is_mask_index_valid(int32_t mask_index) const {
    return mask_index >= 0 &&
        mask_index < Geometry::C_GEOMETRY_TOTAL_CELLS;
  }

  inline bool is_value_valid(uint16_t value) const {
    return value &&
        value >= Location::C_LOCATION_MOVE_MIN &&
        value <= Location::C_LOCATION_MOVE_MAX;
  }

private:
  static constexpr uint16_t C_BOARDSTATE_REMOVELIMIT_MIN { 20 };
  static constexpr uint16_t C_BOARDSTATE_REMOVELIMIT_MAX { 51 };
  static constexpr uint16_t C_BOARDSTATE_SHUFFLELIMIT_MIN { 50 };
  static constexpr uint16_t C_BOARDSTATE_SHUFFLELIMIT_MAX { 100 };

private:
  SetupBoard(const SetupBoard&) = delete;
  SetupBoard operator=(const SetupBoard&) = delete;

};


}
}
}
}

#endif
