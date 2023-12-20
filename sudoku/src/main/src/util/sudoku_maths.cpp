#include <cassert>

#include "sudoku_maths.h"
#include "sudoku_worker.h"

namespace cc {
namespace tools {
namespace sudoku {

thread_local std::random_device Maths::_device;

thread_local std::mt19937 Maths::_generator(_device());

}
}
}
