#ifndef SUDOKU_LIB_HANDLERS_H
#define SUDOKU_LIB_HANDLERS_H

#include <csignal>
#include <exception>
#include <iostream>
#include <memory>

#include "sudoku_globals.h"
#include "sudoku_atomic_flag.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

class Handler final {

public:
  static void signal_handler(int32_t signal_num);

  static void signal_no_memory();

private:
  static AtomicFlagSeqCst _is_locked_flag;

  static std::unique_ptr<uint8_t> _reserved_memory;

private:
  Handler() = delete;

};

}
}
}
}

void load_sudoku_handler() __attribute__((constructor));

void unload_sudoku_handler() __attribute__((destructor));

void load_sudoku_handler() {
  signal(SIGTERM,
      cc::tools::sudoku::lib::Handler::signal_handler);

  signal(SIGINT,
      cc::tools::sudoku::lib::Handler::signal_handler);

  std::set_new_handler(
      cc::tools::sudoku::lib::Handler::signal_no_memory);
}

void unload_sudoku_handler() {

  try {
    cc::tools::sudoku::Globals::do_exit_all_global();

  } catch (const std::exception& e) {
    
    std::cerr << __FILE__
        << " "
        << __LINE__
        << " exception caught: "
        << e.what()
        << std::endl;
    
  } catch (...) {
  
    std::cerr << __FILE__
        << " "
        << __LINE__
        << " unknown exception caught !"
        << std::endl;
  }
}

#endif
