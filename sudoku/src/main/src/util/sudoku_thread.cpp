#include "sudoku_thread.h"

#include "sudoku_log.h"
#include "sudoku_threads.h"

namespace cc {
namespace tools {
namespace sudoku {

Thread::~Thread() {

  try {
    LOGTRACE("destroying ", reinterpret_cast<void*>(this));

    if (_thread.get()) {
      LOGTRACE("joining ", reinterpret_cast<void*>(this));
      _thread->join();
    }

  } catch (const std::exception& e) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " exception caught closing worker on thread: "
        << Threads::get_thread_name()
        << " "
        << e.what()
        << std::endl;

  } catch (...) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " unknown exception caught closing worker on thread: "
        << Threads::get_thread_name()
        << std::endl;

  }
}


}
}
}
