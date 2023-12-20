#include "sudoku_lib_solution.h"
#include "sudoku_lib_common.h"

#include "sudoku_game.h"
#include "sudoku_globals.h"
#include "sudoku_log.h"
#include "sudoku_move.h"
#include "sudoku_router.h"
#include "sudoku_timers.h"
#include "sudoku_threads.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

Solution::Solution(const std::string& request) :
  _request(request),
  _router(Router::get_router()) {
}

uint32_t Solution::get_sudoku_solution(std::vector<std::pair<uint16_t, uint16_t>>& out_moves,
                                       int32_t& out_runtime) {

  LOGINFO("start get sudoku solution");

  Timer2 timer [[maybe_unused]] (out_runtime);

  if (Globals::is_exit_all_global()) {
    return Codes::shutdown_exit();
  }

  std::shared_ptr<WorkI> work(new Game());

  Game* game(static_cast<Game*>(work.get()));

  if (uint32_t result = (Common::setup_game(*game, _request))) {
    LOGWARN("setup failed");
    return result;
  }

  LOGDEBUG("start position: ", game->to_string());

  std::shared_ptr<Router> router(_router.lock());

  if (!router) {
    return Globals::is_exit_all_global() ?
        Codes::shutdown_exit() : Codes::internal_error();
  }

  LOGINFO("router load: ", Common::get_worker_load_summary());

  if (!router->route_load_balance(work)) {

    LOGERROR("server busy.");

    return Codes::server_busy();
  }

  while (!Globals::is_exit_all_global() &&
      !(work->is_processed() ||
          work->is_interrupted())) {

    Threads::do_shorter_to_short_rand_sleep();
  }

  if (Globals::is_exit_all_global() &&
      !work->is_processed()) {
    return Codes::shutdown_exit();
  }

  LOGINFO("RESULT[processed count]: ", (work->is_processed() ? '1' : '0'));

  LOGINFO("RESULT[solved count]: ", (work->is_solved() ? '1' : '0'));

  LOGINFO("RESULT[interrupted count]: ", (work->is_interrupted() ? '1' : '0'));

  Common::transform_moves(*game, out_moves);

  if (!work->is_solved()) {
    return Codes::no_solution();
  }

  return Codes::success();
}

}
}
}
}

