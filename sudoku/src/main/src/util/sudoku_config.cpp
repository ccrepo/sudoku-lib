#include <functional>

#include "sudoku_config.h"

namespace cc {
namespace tools {
namespace sudoku {

bool Config::is_no_level() {
  static const bool no_level((
      static_cast<int>(get_config()->is_log_all())   +
      static_cast<int>(get_config()->is_log_trace()) +
      static_cast<int>(get_config()->is_log_debug()) +
      static_cast<int>(get_config()->is_log_info())  +
      static_cast<int>(get_config()->is_log_warn())  +
      static_cast<int>(get_config()->is_log_error()) +
      static_cast<int>(get_config()->is_log_fatal()))
      == 0);

  return no_level;
}

}
}
}
