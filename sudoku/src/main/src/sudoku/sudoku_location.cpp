#include "sudoku_location.h"

namespace cc {
namespace tools {
namespace sudoku {

std::string Location::to_string() const {
  std::ostringstream os;

  os << Index::to_string()
  		    << " -> ";

  if (_value == USHRT_MAX) {

    os << std::string("-");

  } else {

    os << _value;
  }

  return os.str();
}

Location& Location::operator=(const Location& location) {
  static_cast<Index&>(*this) =
      static_cast<const Index&>(location);

  _value = location._value;

  return (*this);
}

}
}
}

