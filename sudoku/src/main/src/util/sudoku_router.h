#ifndef SUDOKU_ROUTER_H
#define SUDOKU_ROUTER_H

#include <memory>
#include <mutex>
#include <array>

#include "sudoku_workerpool.h"
#include "sudoku_log.h"
#include "sudoku_atomic_counter.h"

namespace cc {
namespace tools {
namespace sudoku {

class Router final {

public:
  ~Router();

private:
  static std::shared_ptr<Router> _router;

public:
  bool route_round_robin(const std::shared_ptr<WorkI>& work,
      bool retry = true);

  bool route_round_robin(const std::vector<std::shared_ptr<WorkI>>& work,
      bool retry = true);

  bool route_load_balance(const std::shared_ptr<WorkI>& work,
      bool retry = true);

  bool route_load_balance(const std::vector<std::shared_ptr<WorkI>>& work,
      bool retry = true);

public:
  static std::weak_ptr<Router> get_router() {
    return _router;
  }

  uint16_t get_worker_pool_loads(
      std::vector<std::pair<uint16_t, uint16_t>>& worker_pool_loads,
      uint16_t start_index = 0,
      bool filter = false) const;

private:
  Router() : _round_robin_route_counter(0),
    _worker_pools(create_worker_pools(
        WorkerPool::C_WORKERPOOL_WORKERS_PER_POOL)) {
  }

private:
  const std::vector<std::shared_ptr<WorkerPool>> create_worker_pools(
      uint16_t num_workers_per_pool) const;

private:
  AtomicCounterU8Relaxed _round_robin_route_counter;

  const std::vector<std::shared_ptr<WorkerPool>> _worker_pools;

private:
  static constexpr uint16_t C_ROUTER_NUM_NON_BATCH_POOLS { 2 };

  static_assert(C_ROUTER_NUM_NON_BATCH_POOLS < WorkerPool::C_WORKERPOOL_WORKERS_POOL_TOTAL,
      "non batch pools must be smaller than the total number of pools");

private:
  Router(const Router&) = delete;
  Router& operator=(const Router&) = delete;

};

}
}
}

#endif
