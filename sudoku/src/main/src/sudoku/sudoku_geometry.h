#ifndef SUDOKU_GEOMETRY_H
#define SUDOKU_GEOMETRY_H

#include <cassert>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>

namespace cc {
namespace tools {
namespace sudoku {

class Geometry {

public:
  Geometry() {
  }

  virtual ~Geometry() {
  }

  Geometry(const Geometry&) {
  }

  Geometry& operator=(const Geometry&) {
    return (*this);
  }

public:
  static constexpr uint16_t C_GEOMETRY_TOTAL_CELLS    { 81 };
  static constexpr uint16_t C_GEOMETRY_CELL_MAX_INDEX { 80 };
  static constexpr uint16_t C_GEOMETRY_CELL_BUF_RCB   { 9 };
  static constexpr uint16_t C_GEOMETRY_BOARD_SIZE     { 9 };
  static constexpr uint16_t C_GEOMETRY_GROUP_MULTIPLE { 3 };
  static constexpr uint16_t C_GEOMETRY_TOTAL_BLOCKS   { 9 };
  static constexpr uint16_t C_GEOMETRY_RANKS[3][3] { {0, 1, 2}, {3, 4, 5}, {6, 7, 8} };
  static constexpr uint16_t C_GEOMETRY_STACKS[3][3] { {0, 3, 6}, {1, 4, 7}, {2, 5, 8} };

private:
  static std::array<uint16_t, C_GEOMETRY_TOTAL_CELLS> index_to_region(
      const std::function<uint16_t(uint16_t)>& f);

private:
  static inline const std::array<uint16_t, C_GEOMETRY_TOTAL_CELLS> _index_to_row {
    index_to_region ( [](uint16_t index) -> uint16_t { return index / C_GEOMETRY_BOARD_SIZE; } )
  };

  static inline const std::array<uint16_t, C_GEOMETRY_TOTAL_CELLS> _index_to_col {

    index_to_region ( [](uint16_t index) -> uint16_t {
      return index % C_GEOMETRY_BOARD_SIZE; } )
  };

  static inline const std::array<uint16_t, C_GEOMETRY_TOTAL_CELLS> _index_to_rank {

    index_to_region ( [](uint16_t index) -> uint16_t {
      return _index_to_row[index] / C_GEOMETRY_GROUP_MULTIPLE; } )
  };

  static inline const std::array<uint16_t, C_GEOMETRY_TOTAL_CELLS> _index_to_stack {

    index_to_region ( [](uint16_t index) -> uint16_t {
      return _index_to_col[index] / C_GEOMETRY_GROUP_MULTIPLE; } )
  };

  static inline const std::array<uint16_t, C_GEOMETRY_TOTAL_CELLS> _index_to_block {

    index_to_region ( [](uint16_t index) -> uint16_t {
      return (_index_to_rank[index] * C_GEOMETRY_GROUP_MULTIPLE) + _index_to_stack[index];
    } )
  };

public:
  static inline uint16_t index_to_row(uint16_t index) {
    return _index_to_row[index];
  }

  static inline uint16_t index_to_col(uint16_t index) {
    return _index_to_col[index];
  }

  static inline uint16_t index_to_rank(uint16_t index) {
    return _index_to_rank[index];
  }

  static inline uint16_t index_to_stack(uint16_t index) {
    return _index_to_stack[index];
  }

  static inline uint16_t index_to_block(uint16_t index) {
    return _index_to_block[index];
  }

public:
  enum E_REGION_TYPE { E_REGION_TYPE_BLOCK, E_REGION_TYPE_COL, E_REGION_TYPE_ROW };

  enum E_ROW_OR_COL { E_ROW_OR_COL_ROW = 0, E_ROW_OR_COL_COL = 1 };

};

}
}
}

#endif
