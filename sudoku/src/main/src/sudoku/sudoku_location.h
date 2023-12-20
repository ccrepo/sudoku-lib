#ifndef SUDOKU_LOCATION_H
#define SUDOKU_LOCATION_H

#include <sstream>
#include <cstdint>

#include "sudoku_index.h"

namespace cc {
namespace tools {
namespace sudoku {

class Move;

class Location : public Index {

public:
  Location() :
    Index(USHRT_MAX),
    _value(USHRT_MAX) {
  }

  explicit Location(uint16_t index, uint16_t value) :
		    Index(index),
		    _value(value) {
  }

  explicit Location(Index index, uint16_t value) :
		    Index(index),
		    _value(value) {
  }

  explicit Location(const Location& location) :
		    Index(static_cast<const Index&>(location)) {
    _value = location._value;
  }

  Location& operator=(const Location& location);

  virtual ~Location() override {
  }

public:
  std::string to_string() const;

public:
  static constexpr uint16_t C_LOCATION_MOVE_MIN { 1 };
  static constexpr uint16_t C_LOCATION_MOVE_MAX { 9 };

private:
  friend class Move;

private:
  uint16_t _value;
};

}
}
}

#endif
