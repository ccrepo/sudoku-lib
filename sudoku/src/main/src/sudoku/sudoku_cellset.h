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

  ~CellSet() {
  }

  CellSet(const CellSet& cellset) :
    _cells(cellset._cells) {
  }

  CellSet& operator=(const CellSet& cellset) {
    _cells = cellset._cells;

    return (*this);
  }

public:
  bool check_solved() const;

public:
  bool do_move_on_cellset(const Move& move);

public:
  const Cell& get_cell(uint16_t index) const {
    return _cells[index];
  }

  Cell& get_cell(uint16_t index) {
    return _cells[index];
  }

  const std::array<Cell, Geometry::C_GEOMETRY_TOTAL_CELLS>& get_cells() const {
    return _cells;
  }

  bool get_possible_moves(std::vector<Move>& buffer,
      bool return_all) const;

  size_t get_size() const {
    return _cells.size();
  }

  std::array<uint16_t, Geometry::C_GEOMETRY_TOTAL_CELLS> get_values() const;

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
