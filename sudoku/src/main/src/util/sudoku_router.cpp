#include <cassert>
#include <climits>
#include <numeric>
#include <memory>

#include "sudoku_router.h"

namespace cc {
namespace tools {
namespace sudoku {

std::shared_ptr<Router> Router::_router(new Router());

const std::vector<std::shared_ptr<WorkerPool>> Router::create_worker_pools(
    uint16_t num_workers_per_pool) const {

  if (!num_workers_per_pool) {
    assert(!"workers per pool must be above zero");
  }

  std::vector<std::shared_ptr<WorkerPool>> worker_pools;

  for (auto i(0); i < WorkerPool::C_WORKERPOOL_WORKERS_POOL_TOTAL; ++i) {

    worker_pools.push_back(std::shared_ptr<WorkerPool>(new WorkerPool(num_workers_per_pool)));

    LOGTRACE("created worker pool ", reinterpret_cast<void*>(
        worker_pools[worker_pools.size()-1].get()));
  }

  return worker_pools;
}

Router::~Router() {
  LOGTRACE("destroying ", reinterpret_cast<void*>(this));
}

bool Router::route_round_robin(const std::shared_ptr<WorkI>& work, bool retry) {
  auto index(_round_robin_route_counter.increment()%
      WorkerPool::C_WORKERPOOL_WORKERS_POOL_TOTAL);

  return _worker_pools[index]->push(work, retry);
}

bool Router::route_round_robin(const std::vector<std::shared_ptr<WorkI>>& work, bool retry) {
  auto index(_round_robin_route_counter.increment()%
      WorkerPool::C_WORKERPOOL_WORKERS_POOL_TOTAL);

  return _worker_pools[index]->push(work, retry);
}

bool Router::route_load_balance(const std::shared_ptr<WorkI>& work,
    bool retry) {

  thread_local static std::vector<std::pair<uint16_t, uint16_t>> worker_pool_loads;

  worker_pool_loads.clear();

  if (!get_worker_pool_loads(worker_pool_loads,
      0,
      true)) {
    return false;
  }

  if (worker_pool_loads.empty()) {
    return false;
  }

  auto worker_pool_load = std::min_element(worker_pool_loads.begin(), worker_pool_loads.end(),
      [](const auto& load1, const auto& load2) {
    return load1.second < load2.second;
  });

  return _worker_pools[worker_pool_load->first]->push(work, retry);
}

bool Router::route_load_balance(const std::vector<std::shared_ptr<WorkI>>& work,
    bool retry) {

  thread_local static std::vector<std::pair<uint16_t, uint16_t>> worker_pool_loads;

  worker_pool_loads.clear();

  if (!get_worker_pool_loads(worker_pool_loads,
      C_ROUTER_NUM_NON_BATCH_POOLS,
      true)) {

    return false;
  }

  if (worker_pool_loads.empty()) {
    return false;
  }

  auto worker_pool_load = std::min_element(worker_pool_loads.begin(), worker_pool_loads.end(),
      [](const auto& load1, const auto& load2) {
    return load1.second < load2.second;
  });

  return _worker_pools[worker_pool_load->first]->push(work, retry);
}

uint16_t Router::get_worker_pool_loads(
    std::vector<std::pair<uint16_t, uint16_t>>& worker_pool_loads,
    uint16_t start_index,
    bool filter) const {

  uint32_t lowest_size(UINT_MAX);

  if (start_index < _worker_pools.size()) {

    for (uint16_t i(start_index); i < _worker_pools.size(); ++i) {

      if (filter) {

        auto size(_worker_pools[i]->get_size());

        if (size < lowest_size) {

          lowest_size = size;

          worker_pool_loads.push_back( { i, size } );
        }

        continue;
      }

      worker_pool_loads.push_back( { i, _worker_pools[i]->get_size() } );
    }
  }

  return worker_pool_loads.size();
}

}
}
}

