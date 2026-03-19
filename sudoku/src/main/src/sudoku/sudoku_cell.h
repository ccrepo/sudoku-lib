#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <array>
#include <cstdint>

#include "sudoku_geometry.h"
#include "sudoku_mask.h"

namespace cc {
namespace tools {
namespace sudoku {

class Move;

class Cell final {

public:
  Cell() :
    _value(0),
    _mask() {
  }

  ~Cell() {
  }

  Cell(const Cell& cell) : _value(cell._value),
      _mask(cell._mask) {
  }

  Cell& operator=(const Cell& cell);

public:
  bool can_adjust(const Move& move) const;

  bool can_move(const Move& move) const;

  bool can_move(uint16_t value) const;

public:
  bool do_move_on_cell(const Move& move);

  bool do_adjust(const Move& move);

  inline bool do_keep_matches(uint16_t bitmask) {
    return _mask.do_keep_matches(bitmask);
  }

  inline bool do_remove_matches(uint16_t bitmask) {
    return _mask.do_remove_matches(bitmask);
  }

public:
  inline uint16_t get_value() const {
    return _value;
  }

  inline const Mask& get_mask() const {
    return _mask;
  }

  inline uint16_t get_number_potential_moves() const {
    return _mask.get_number_potential_moves();
  }

public:
  inline uint16_t is_move_exists(uint16_t value) const {
    return _mask.is_move_exists(value);
  }

  inline bool is_moves_exist() const {
    return _mask.is_moves_exist();
  }

  inline bool is_solved() const {
    return _value &&
        !_mask.is_moves_exist();
  }

public:
  std::string to_string(bool is_verbose = false) const;

public:
  static constexpr std::array<uint16_t, Geometry::C_GEOMETRY_BOARD_SIZE>
  C_CELL_VALUES { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

private:
  uint16_t _value;
  Mask _mask;
};

}
}
}

#endif
