#ifndef SUDOKU_GLOBALS_H
#define SUDOKU_GLOBALS_H

#include "sudoku_atomic_flag.h"

namespace cc {
namespace tools {
namespace sudoku {

class Globals final {

public:
  static inline void do_exit_all_global() {
    _exit_all_global_flag.test_and_set();
  }

  static inline bool is_exit_all_global() {
    return _exit_all_global_flag.test();
  }

private:
  static AtomicFlagSemiRelaxed _exit_all_global_flag;

private:
  Globals() = delete;

};

}
}
}

#endif



