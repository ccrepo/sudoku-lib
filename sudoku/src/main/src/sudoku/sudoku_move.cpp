#include "sudoku_utility.h"
#include "sudoku_move.h"

namespace cc {
namespace tools {
namespace sudoku {

bool Move::parse_moves(const std::string& s, std::vector<Move>& moves) {

  std::vector<std::string> tokens;

  std::vector<Move> buffer;

  if (!Utility::split(s, tokens) ||
      (tokens.size() != Geometry::C_GEOMETRY_TOTAL_CELLS)) {
    return false;
  }

  for (uint16_t i(0); i < Geometry::C_GEOMETRY_TOTAL_CELLS; ++i) {

    const std::string& token(tokens[i]);

    if (token.size() != 1 ||
        !Utility::is_digit(token[0])) {
      return false;
    }

    if (token[0] != '0') {
      buffer.push_back( Move {i, Utility::to_digit(token[0]), 0} );
    }
  }

  std::copy(buffer.begin(), buffer.end(),
      std::back_inserter(moves));

  return true;
}

std::string Move::to_string() const {
  std::ostringstream os;

  os << Location::to_string()
			    << "(";

  if (_weight == USHRT_MAX) {
    os << '-';
  } else {
    os << _weight;
  }

  os << ")";

  return os.str();
}

Move& Move::operator=(const Move& move) {
  static_cast<Location&>(*this) =
      static_cast<const Location&>(move);

  _weight = move._weight;

  return (*this);
}

bool Move::operator==(const Move& move) const {
  return (_weight == move._weight) &&
      (_index == move._index) &&
      (_value == move._value);
}

bool Move::operator<(const Move& move) const {
  if (_weight == move._weight) {
    if (get_index() == move.get_index()) {
      return get_value() < move.get_value();
    }

    return get_index() < move.get_index();
  }

  return _weight < move._weight;
}

bool Move::operator!=(const Move& move) const {
  return !(this->operator==(move));
}

}
}
}
