#include "sudoku_cell.h"
#include "sudoku_move.h"
#include "sudoku_log.h"

namespace cc {
namespace tools {
namespace sudoku {

bool Cell::can_adjust(const Move& move) const {
  return _mask.can_adjust(get_value(),
      move.get_value());
}

bool Cell::can_move(const Move& move) const {
  return can_move(move.get_value());
}

bool Cell::can_move(uint16_t value) const {
  return !_value &&
      _mask.can_move(value);
}

bool Cell::do_adjust(const Move& move) {
  return _mask.can_adjust(get_value(), move.get_value()) &&
      _mask.do_adjust(move.get_value());
}

bool Cell::do_move_on_cell(const Move& move) {
  if (_value) {
    return false;
  }

  if (!_mask.can_move(move.get_value())) {
    return false;
  }

  _value = move.get_value();

  _mask.do_move_on_mask();

  return true;
}

std::string Cell::to_string(bool is_verbose) const {

  if (!is_verbose) {
    return std::to_string(_value);
  }

  std::ostringstream os;

  os << _value
      << "/"
      << _mask.to_string();

  return os.str();
}

Cell& Cell::operator=(const Cell& cell) {
  _value = cell._value;
  _mask = cell._mask;

  return (*this);
}

}
}
}
