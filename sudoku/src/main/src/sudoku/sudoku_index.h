#ifndef SUDOKU_INDEX_H
#define SUDOKU_INDEX_H

#include <sstream>
#include <cstdint>
#include <climits>

#include "sudoku_geometry.h"

namespace cc {
namespace tools {
namespace sudoku {

class Move;

class Index {

public:
  Index() :
    _index(USHRT_MAX) {
  }

  explicit Index(uint16_t index) :
		    _index(index) {
  }

  explicit Index(const Index& index) {
    _index = index._index;
  }

  virtual ~Index() {
  }

  Index& operator=(const Index& index) {
    _index = index._index;
    return (*this);
  }

  bool operator==(const Index& index) const {
    return _index == index._index;
  }

  bool operator==(uint16_t index) const {
    return _index == index;
  }

public:
  inline uint16_t get_block() const {
    return Geometry::index_to_block(_index);
  }

  inline uint16_t get_col() const {
    return Geometry::index_to_col(_index);
  }

  inline uint16_t get_index() const {
    return _index;
  }

  inline uint16_t get_row() const {
    return Geometry::index_to_row(_index);
  }

  std::string to_string() const;

public:
  static bool is_in_same_block(
      const std::vector<Index>& index_list);

  static bool is_in_same_col(
      const std::vector<Index>& index_list);

  static bool is_in_same_row(
      const std::vector<Index>& index_list);

private:
  friend class Move;

private:
  uint16_t _index;
};

}
}
}

#endif
