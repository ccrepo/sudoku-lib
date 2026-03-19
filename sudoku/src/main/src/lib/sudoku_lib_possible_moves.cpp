#include "sudoku_lib_possible_moves.h"
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

PossibleMoves::PossibleMoves(const std::string& request) :
  _request(request),
  _router(Router::get_router()) {
}

uint32_t PossibleMoves::get_sudoku_possible_moves(std::vector<std::pair<uint16_t, uint16_t>>& out_moves,
                                                  int32_t& out_runtime) {
  
  LOGINFO("start get sudoku possible moves");

  Timer2 timer [[maybe_unused]] (out_runtime);

  if (Globals::is_exit_all_global()) {
    return Codes::shutdown_exit();
  }

  Game game;

  if (uint32_t result = (Common::setup_game(game, _request))) {
    LOGWARN("setup failed");
    return result;
  }

  LOGDEBUG("start position: ", game.to_string());

  std::vector<Move> possible_moves;

  if (!Common::get_all_possible_moves(game, possible_moves)) {
    LOGWARN("get all possible moves failed");
    return Codes::internal_error();
  }

  std::shared_ptr<Router> router(_router.lock());

  if (!router) {
    return Globals::is_exit_all_global() ?
        Codes::shutdown_exit() : Codes::internal_error();
  }

  LOGINFO("router load: ", Common::get_worker_load_summary());

  std::vector<std::shared_ptr<WorkI>> works;

  std::vector<std::shared_ptr<WorkI>> work_batch;

  uint16_t not_queued_count(0);

  for (const auto& possible_move : possible_moves) {

    std::shared_ptr<WorkI> work(
        new Game(std::unique_ptr<Board>(
            new Board(game.get_root_board()))));

    Game* child(static_cast<Game*>(work.get()));

    LOGTRACE("child : ",
        child->to_string());

    if (child->do_setup( { possible_move }, false )) {

      LOGDEBUG("queued game ", child->get_game_id());

      works.push_back(work);

      work_batch.push_back(work);

      if (work_batch.size() >= C_POSSIBLE_MOVES_BATCH_SIZE) {

        if (router->route_load_balance(work_batch, false)) {
          work_batch.clear();
        }

      }

    } else if (child->is_solved()) {

      LOGDEBUG("already solved game ", child->get_game_id());

      works.push_back(work);

      child->set_is_processed();

    } else {

      LOGDEBUG("not queued game ", child->get_game_id());

      ++not_queued_count;
    }
  }

  if (!work_batch.empty()) {

    if (!router->route_load_balance(work_batch)) {

      LOGERROR("server busy.");

      return Codes::server_busy();
    }

    work_batch.clear();
  }

  while (!Globals::is_exit_all_global()) {

    if ((WorkI::get_processed_count(works) +
        WorkI::get_interrupted_count(works) +
        not_queued_count) == possible_moves.size()) {

      break;
    }

    Threads::do_shorter_to_short_rand_sleep();
  }

  LOGINFO("RESULT[possible move total]: ", possible_moves.size());

  LOGINFO("RESULT[processed total]: ", WorkI::get_processed_count(works));

  LOGINFO("RESULT[interrupted total]: ", WorkI::get_interrupted_count(works));

  LOGINFO("RESULT[solved total]: ", WorkI::get_solved_count(works));

  LOGINFO("RESULT[un-queued total]: ", not_queued_count);

  if (Globals::is_exit_all_global()) {
    return Codes::shutdown_exit();
  }

  std::for_each(works.begin(), works.end(),
      [&out_moves](const std::shared_ptr<WorkI>& work) {

    if (work->is_solved()) {

      const Game* game(static_cast<const Game*>(work.get()));

      if (game->get_root_board().has_move()) {

        const Move& move(
            game->get_root_board().get_last_move());

        out_moves.push_back(
            {move.get_index(), move.get_value()} );
      }
    }
  });
  
  return Codes::success();
}

}
}
}
}

