#include "sudoku_autoset.h"
#include "sudoku_autocall.h"
#include "sudoku_clocks.h"
#include "sudoku_globals.h"
#include "sudoku_log.h"
#include "sudoku_queue.h"
#include "sudoku_router.h"
#include "sudoku_threads.h"
#include "sudoku_worker.h"
#include "sudoku_workI.h"
#include "sudoku_atomic_flag.h"

namespace cc {
namespace tools {
namespace sudoku {

Worker::Worker(const std::shared_ptr<Queue>& queue,
    const void * const worker_pool) :
    _queue(queue),
		_is_exited(),
    _is_exit_worker(),
		_worker_pool(worker_pool),
		_run_callback_lambda(get_run_callback_lambda()) {
  start(_run_callback_lambda);
}

void Worker::run() {

  LOGTRACE("start worker run loop ",
      _worker_pool,
      ".",
      reinterpret_cast<void*>(this));

  Autoset<AtomicFlagRelAcq> autoset(_is_exited);

  int counter(0);

  while (!Globals::is_exit_all_global() &&
      !_is_exit_worker.test()) {

    ++counter;

    std::vector<std::pair<std::shared_ptr<WorkI>, std::shared_ptr<Autocall>>> work;

    LOGALL("loop ",
        _worker_pool,
        ".",
        reinterpret_cast<void*>(this));

    if (_queue->pop(work, C_WORKER_BATCH_SIZE)) {

      for (auto& w : work) {

        try {

          w.first->do_solve();

          w.first->set_is_processed();

          w.second->do_cancel_autocall();

        }  catch (const std::exception& e) {

          std::cerr << __FILE__
              << " "
              << __LINE__
              << " exception caught worker thread : "
              << Threads::get_thread_name()
              << " "
              << e.what()
              << std::endl;

        } catch (...) {

          std::cerr << __FILE__
              << " "
              << __LINE__
              << " unknown exception caught in thread "
              << Threads::get_thread_name()
              << std::endl;
        }

      }

    } else if (counter < C_WORKER_READ_ATTEMPTS_BEFORE_COND) {

      Threads::do_minimum_to_miniscule_rand_sleep();

      continue;

    } else if (!_queue->do_condition_wait()) {

      Threads::do_minimum_to_miniscule_rand_sleep();
    }

    counter = 0;
  }

  LOGTRACE("end worker run loop ",
      _worker_pool,
      ".",
      reinterpret_cast<void*>(this));
}

Worker::~Worker() {
}

}
}
}

