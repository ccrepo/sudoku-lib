#include "sudoku_workI.h"

#include "sudoku_log.h"

namespace cc {
namespace tools {
namespace sudoku {

uint64_t WorkI::get_processed_count(
    const std::vector<std::shared_ptr<WorkI>>& work) {

  return std::count_if(work.begin(), work.end(), [](auto& w) {
    return w->is_processed();
  });
}

uint64_t WorkI::get_solved_count(
    const std::vector<std::shared_ptr<WorkI>>& work) {

  return std::count_if(work.begin(), work.end(), [](auto& w) {
    return w->is_solved();
  });
}

uint64_t WorkI::get_interrupted_count(
    const std::vector<std::shared_ptr<WorkI>>& work) {

  return std::count_if(work.begin(), work.end(), [](auto& w) {
    return !w->is_processed() &&
        w->is_interrupted();
  });
}

WorkI::~WorkI() {
  LOGTRACE("destroying ", reinterpret_cast<void*>(this));
}

}
}
}
