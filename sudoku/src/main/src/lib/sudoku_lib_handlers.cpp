#include "sudoku_lib_handlers.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

AtomicFlagSeqCst Handler::_is_locked_flag;

std::unique_ptr<uint8_t> Handler::_reserved_memory(new uint8_t[1024 * 10]);

void Handler::signal_handler(int32_t signal_num) {
  
  std::cout << "stopping["
  << signal_num << "] ..."
  << std::endl;
  
  std::cout.flush();
  
  cc::tools::sudoku::Globals::do_exit_all_global();
  
}

void Handler::signal_no_memory() {
  
  if (!_is_locked_flag.test_and_set()) {
    
    _reserved_memory.reset(0);
    
    std::cerr << "out of memory"
    << std::endl;;
    
    std::abort();
  }
  
}

}
}
}
}

