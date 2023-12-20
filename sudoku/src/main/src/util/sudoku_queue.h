#ifndef SUDOKU_QUEUE_H
#define SUDOKU_QUEUE_H

#include <deque>
#include <memory>
#include <mutex>
#include <vector>
#include <memory>
#include <condition_variable>
#include <shared_mutex>
#include <utility>
#include <iostream>

#include "sudoku_types.h"
#include "sudoku_autocall.h"
#include "sudoku_atomic_flag.h"
#include "sudoku_atomic_value.h"

namespace cc {
namespace tools {
namespace sudoku {

class WorkI;

class Queue final {

public:
  Queue();

  ~Queue();

public:
  bool push(const std::shared_ptr<WorkI>& element,
      bool retry = true);

  bool push(const std::vector<std::shared_ptr<WorkI>>& elements,
      bool retry = true);

  bool pop(std::shared_ptr<WorkI>& element, bool retry = true);

  bool pop(std::vector<std::shared_ptr<WorkI>>& elements, uint32_t pop_count,
      bool retry = true);

  bool pop(std::vector<std::pair<std::shared_ptr<WorkI>, std::shared_ptr<Autocall>>>& elements,
      uint32_t pop_count, bool retry = true);

public:
  bool do_condition_wait();

  bool do_condition_wake();

  bool do_exit_queue();

public:
  uint32_t get_queue_size() const {
    return _queue_size_value.get();
  }

private:
  std::deque<std::shared_ptr<WorkI>> _elements;

  AtomicValueU32Relaxed _queue_size_value;

  std::timed_mutex _write_lock_mutex;

  std::shared_mutex _condition_mutex;

  std::condition_variable_any _condition_variable;

  AtomicFlagSeqCst _exit_queue_flag;

private:
  bool is_exit() const;

private:
  Queue(const Queue&) = delete;
  Queue& operator=(const Queue&) = delete;

private:
  static constexpr uint16_t C_QUEUE_WRITE_LOCK_RETRIES { 5 };
  static constexpr uint16_t C_QUEUE_CONDITION_VARIABLE_WAIT_TIMEOUT { 15000 };

};

}
}
}

#endif
