#ifndef SUDOKU_WORKER_H
#define SUDOKU_WORKER_H

#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <thread>
#include <functional>

#include "sudoku_thread.h"
#include "sudoku_maths.h"
#include "sudoku_types.h"
#include "sudoku_atomic_flag.h"

namespace cc {
namespace tools {
namespace sudoku {

class Queue;

class Worker final : private Thread {

public:
  Worker(const std::shared_ptr<Queue>& queue,
      const void* const worker_pool);

  virtual ~Worker() override;

public:
  static constexpr uint16_t C_WORKER_READ_ATTEMPTS_BEFORE_COND { 5 };
  static constexpr uint16_t C_WORKER_BATCH_SIZE { 50 };

public:
  inline bool is_exited() const {
    return _is_exited.test();
  }

public:
  void run();

  inline void do_exit_worker() {
    _is_exit_worker.set();
  }

  std::function<void ()> get_run_callback_lambda() {
    return [this]() {
      this->run();
    };
  }

private:
  std::shared_ptr<Queue> _queue;

  AtomicFlagRelAcq _is_exited;

  AtomicFlagSemiRelaxed _is_exit_worker;

  const void* const _worker_pool;

  std::function<void ()> _run_callback_lambda;

private:
  Worker(const Worker&) = delete;
  Worker& operator=(const Worker&) = delete;

};

}
}
}

#endif
