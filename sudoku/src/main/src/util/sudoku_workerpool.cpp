#include <sstream>

#include "sudoku_workerpool.h"
#include "sudoku_log.h"

namespace cc {
namespace tools {
namespace sudoku {

const std::vector<std::shared_ptr<Worker>> WorkerPool::create_workers(
    uint16_t num_workers_per_pool) const {

  LOGTRACE("creating workers");

  std::vector<std::shared_ptr<Worker>> workers;

  for (auto i(0); i < num_workers_per_pool; ++i) {
    workers.push_back(std::shared_ptr<Worker>(
        new Worker(_queue, reinterpret_cast<const void*>(this))));
  }

  LOGTRACE("created workers");

  return workers;
}

bool WorkerPool::push(const std::shared_ptr<WorkI>& work, bool retry) {

  if (_is_exit_worker_pool.test()) {

    _queue->do_condition_wake();

    return false;
  }

  bool result = _queue->push(work, retry);

  _queue->do_condition_wake();

  return result;
}

bool WorkerPool::push(const std::vector<std::shared_ptr<WorkI>>& work, bool retry) {

  if (_is_exit_worker_pool.test()) {

    _queue->do_condition_wake();

    return false;
  }

  bool result = _queue->push(work, retry);

  _queue->do_condition_wake();

  return result;
}

WorkerPool::WorkerPool(uint16_t num_workers_per_pool) :
    _queue(new Queue()),
    _workers(create_workers(num_workers_per_pool)) {

  LOGTRACE("creating ", reinterpret_cast<void*>(this));
}

void WorkerPool::do_exit_worker_pool() {
  _is_exit_worker_pool.set();

  for (std::shared_ptr<Worker>& worker : _workers) {
    worker->do_exit_worker();
  }

  _queue->do_condition_wake();
}

WorkerPool::~WorkerPool() {

  LOGTRACE("destroying ", reinterpret_cast<void*>(this));

  do_exit_worker_pool();

  try {
    _workers.clear();

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

bool WorkerPool::is_exited_worker_pool() const {
  return std::all_of(_workers.begin(), _workers.end(),
      [](auto& worker) { return worker->is_exited(); });
}

}
}
}
