#ifndef SUDOKU_WORKERPOOL_H
#define SUDOKU_WORKERPOOL_H

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

#include "sudoku_worker.h"
#include "sudoku_queue.h"
#include "sudoku_atomic_flag.h"

namespace cc {
namespace tools {
namespace sudoku {

class WorkerPool final {

public:
  static constexpr uint16_t C_WORKERPOOL_WORKERS_TOTAL { 120 };
  static constexpr uint16_t C_WORKERPOOL_WORKERS_PER_POOL { 6 };
  static constexpr uint16_t C_WORKERPOOL_WORKERS_POOL_TOTAL {
    C_WORKERPOOL_WORKERS_TOTAL/C_WORKERPOOL_WORKERS_PER_POOL };

public:
  explicit WorkerPool(uint16_t num_workers_per_pool);

  ~WorkerPool();

public:
  bool push(const std::shared_ptr<WorkI>& work, bool retry = true);

  bool push(const std::vector<std::shared_ptr<WorkI>>& work, bool retry = true);

  void do_exit_worker_pool();

  bool is_exited_worker_pool() const;

  inline uint32_t get_size() const {
    return _queue->get_queue_size();
  }

private:
  std::shared_ptr<Queue> _queue;

  std::vector<std::shared_ptr<Worker>> _workers;

  AtomicFlagSeqCst _is_exit_worker_pool;

private:
  const std::vector<std::shared_ptr<Worker>> create_workers(
      uint16_t num_workers_per_pool) const;

private:
  WorkerPool(const WorkerPool&) = delete;
  WorkerPool& operator=(const WorkerPool&) = delete;

private:
  static_assert((static_cast<int64_t>(C_WORKERPOOL_WORKERS_TOTAL)
      - C_WORKERPOOL_WORKERS_PER_POOL) > 0, "worker pool size too small");

  static_assert(!(C_WORKERPOOL_WORKERS_TOTAL % C_WORKERPOOL_WORKERS_PER_POOL),
      "worker pool size not multiple of workers per queue");

  static_assert(C_WORKERPOOL_WORKERS_POOL_TOTAL,
      "number of pools must be above zero");

};

}
}
}

#endif

