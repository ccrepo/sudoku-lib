#include "sudoku_lib_random_game.h"
#include "sudoku_lib_setup_board.h"
#include "sudoku_lib_common.h"

#include "sudoku_game.h"
#include "sudoku_geometry.h"
#include "sudoku_globals.h"
#include "sudoku_log.h"
#include "sudoku_mask.h"

#include "sudoku_move.h"
#include "sudoku_timers.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {
namespace random_game {
  const char* start_position = "1 2 3 4 5 6 7 8 9 4 5 6 7 8 9 1 2 3 7 8 9 1 2 3 4 5 6 "
      "2 3 1 6 7 4 8 9 5 8 7 5 9 1 2 3 6 4 6 9 4 5 3 8 2 1 7 "
      "3 1 7 2 6 5 9 4 8 5 4 2 8 9 7 6 3 1 9 6 8 3 4 1 5 7 2";
}

const std::string RandomGame::_start_position(random_game::start_position);

RandomGame::RandomGame() :
  _request(RandomGame::_start_position) {
}

uint32_t RandomGame::get_random_game(std::vector<std::pair<uint16_t, uint16_t>>& out_moves [[maybe_unused]], // NNN - remove
                                       int32_t& out_runtime) {

  LOGINFO("start get sudoku random game");

  Timer2 timer [[maybe_unused]] (out_runtime);

  if (Globals::is_exit_all_global()) {
    return Codes::shutdown_exit();
  }

  const std::shared_ptr<Game> game(new Game());

  if (uint32_t result = (Common::setup_game(*(game.get()), _request, true))) {
    LOGERROR("setup failed");
    return result;
  }

  LOGDEBUG("game setup: ", game->to_string());

  std::shared_ptr<SetupBoard> setup_board(new SetupBoard(game->get_root_board()));

  LOGDEBUG("board setup: ", setup_board->to_string());

  if (!setup_board->is_valid()) {
    LOGERROR("creation failed");
    return Codes::internal_error();
  }

  if (!setup_board->do_setup()) {
    LOGERROR("do setup on setup board failed");
    return Codes::no_solution();
  }

  /*
  if (Globals::is_exit_all_global()) {
    return Codes::shutdown_exit();
  }

  LOGINFO("RESULT[processed count]: 1");

  Common::transform_moves(*(game.get()), out_moves);
  */

  return Codes::success();
}

}
}
}
}

