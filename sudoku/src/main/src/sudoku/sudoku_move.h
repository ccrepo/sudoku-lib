#ifndef SUDOKU_MOVE_H
#define SUDOKU_MOVE_H

#include <sstream>
#include <cstdint>

#include "sudoku_location.h"
#include "sudoku_geometry.h"

namespace cc {
namespace tools {
namespace sudoku {

class Move final : public Location {

public:
  Move() :
    Location(),
    _weight(USHRT_MAX) {
  }

  explicit Move(uint16_t index, uint16_t value, uint16_t weight) :
		    Location(index, value),
		    _weight(weight) {
  }

  explicit Move(Location location, uint16_t weight) :
		    Location(location),
		    _weight(weight) {
  }

  Move(const Move& move) :
    Location(static_cast<const Location&>(move)) {
    _weight = move._weight;
  }

  virtual ~Move() override {
  }

public:
  Move& operator=(const Move& move);

  bool operator==(const Move& move) const;

  bool operator<(const Move& move) const;

  bool operator!=(const Move& move) const;

public:
  inline uint16_t get_weight() const {
    return _weight;
  }

  inline uint16_t get_value() const {
    return Location::_value;
  }

  inline uint16_t get_block() const {
    return Geometry::index_to_block(_index);
  }

  inline uint16_t get_col() const {
    return Geometry::index_to_col(_index);
  }

  inline uint16_t get_row() const {
    return Geometry::index_to_row(_index);
  }

public:
  std::string to_string() const;

public:
  static bool parse_moves(const std::string& s,
      std::vector<Move>& moves);

private:
  uint16_t _weight;
};

}
}
}

#endif
