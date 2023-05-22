#ifndef SUDOKU_CELLSET_H
#define SUDOKU_CELLSET_H

#include <array>
#include <cstdint>

#include "sudoku_geometry.h"
#include "sudoku_mask.h"
#include "sudoku_cell.h"

namespace cc {
namespace tools {
namespace sudoku {

class Move;

class CellSet final {
public:
  CellSet() {
  }

  virtual ~CellSet() {
  }

  CellSet(const CellSet& cellset) :
    _cells(cellset._cells) {
  }

  CellSet& operator=(const CellSet& cellset) {
    _cells = cellset._cells;

    return (*this);
  }

public:
  Cell& get_cell(uint16_t index) {
    return _cells[index];
  }

public:
  bool check_solved() const;

public:
  bool do_move(const Move& move);

public:
  const std::array<Cell, Geometry::C_GEOMETRY_TOTAL_CELLS>& get_cells() const {
    return _cells;
  }

  bool get_possible_moves(std::vector<Move>& buffer,
      bool return_all) const;

  uint16_t get_weight(uint16_t index, uint16_t value) const;

public:
  bool is_move_possible(const Move& move) const;

public:
  std::string to_string(bool is_verbose = false) const;


private:
  std::array<Cell, Geometry::C_GEOMETRY_TOTAL_CELLS> _cells;

private:
  static constexpr uint16_t C_CELLSET_DETERMINSTIC_THRESHOLD { 20 };

};


}
}
}

#endif
