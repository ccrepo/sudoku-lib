#ifndef SUDOKU_GLOBALS_H
#define SUDOKU_GLOBALS_H

#include <atomic>

namespace cc {
namespace tools {
namespace sudoku {

class Globals final {

public:
  static void do_exit_all_global() {
    _exit_all_global.store(true);
  }

  static bool is_exit_all_global() {
    if (_exit_all_global.load()) {
      return true;
    }

    return false;
  }

private:
  static std::atomic<bool> _exit_all_global;

private:
  Globals() = delete;

};

}
}
}

#endif


