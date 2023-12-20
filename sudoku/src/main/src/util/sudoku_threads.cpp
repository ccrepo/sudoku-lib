#include <iostream>

#include "sudoku_threads.h"

namespace cc {
namespace tools {
namespace sudoku {

const std::string Threads::_thread_desc_prefix("thread-");

AtomicCounterU64Relaxed Threads::_thread_id_counter(0);

void Threads::do_sleep(uint32_t ms) {
  try {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
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

}
}
}
