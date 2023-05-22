#ifndef SUDOKU_AUTOCALL_H
#define SUDOKU_AUTOCALL_H

#include <atomic>
#include <functional>

#include "sudoku_globals.h"
#include "sudoku_workI.h"

namespace cc {
namespace tools {
namespace sudoku {

class Autocall final {

public:
  Autocall(const std::shared_ptr<WorkI>& work) :
    _cancelled(false),
    _work(work) {
  }

  virtual ~Autocall() {
    if (!_cancelled) {
      if (!Globals::is_exit_all_global()) {
        if (std::shared_ptr<WorkI> work = _work.lock()) {
          const std::function<void()> callback(work->get_autocall_callback_lambda());
          callback();
        }
      }
    }
  }

  void do_cancel_autocall() {
    _cancelled.store(true);
  }

private:
  std::atomic<bool> _cancelled;
  std::weak_ptr<WorkI> _work;

private:
  Autocall(const Autocall&) = delete;
  Autocall& operator=(const Autocall&) = delete;

};

}
}
}

#endif
