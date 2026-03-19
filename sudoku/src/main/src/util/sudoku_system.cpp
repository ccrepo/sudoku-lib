#include <cstring>

#include "sudoku_system.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace system {

std::string getenv(const std::string& name) {

  static char *value(std::getenv(name.c_str()));

  if (value != nullptr &&
      strlen(value)) {

    return std::string(value);
  }

  return std::string();
}

}
}
}
}
