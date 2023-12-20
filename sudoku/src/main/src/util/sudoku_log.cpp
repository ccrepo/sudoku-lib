#include "sudoku_log.h"
#include "sudoku_threads.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace logger {

thread_local const std::string thread_name( Threads::get_thread_name() );

}
}
}
}
