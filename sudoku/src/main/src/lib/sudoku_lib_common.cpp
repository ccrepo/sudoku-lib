
#include <iostream>
#include <vector>

#include "sudoku_api.h"

#include "sudoku_lib_codes.h"
#include "sudoku_lib_common.h"

#include "sudoku_board.h"
#include "sudoku_game.h"
#include "sudoku_log.h"
#include "sudoku_move.h"
#include "sudoku_router.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

const bool Common::_is_char_signed { std::numeric_limits<char>::is_signed };

bool Common::check_parameters(const char* request,
    uint8_t* response,
    int32_t* runtime) {

  if (!request ||
      !response ||
      !runtime) {
    return false;
  }

  return true;
}

void Common::copy_n(uint8_t* destination,
    const char* source,
    uint32_t n) {

  if (is_char_signed()) {
    for (uint64_t i(0); i < n; ++i) {
      if (!source[i]) {
        break;
      }

      destination[i] = (source[i] <= 1) ?
          static_cast<unsigned char>(1) : source[i];
    }
  } else {
    strncpy(reinterpret_cast<char*>(destination), source, n);
  }
}

uint32_t Common::setup_board(Game& game,
    const std::string& position) {

  LOGDEBUG("start setup board");

  std::vector<Move> setup_moves_buffer;

  if (!Move::parse_moves(position, setup_moves_buffer)) {

    LOGERROR("invalid parameters. parse failed.");

    return Codes::bad_parameter();
  }

  for (const Move& move : setup_moves_buffer) {
    LOGTRACE("queued setup move: ", move.to_string());
  }

  if (!game.do_setup(setup_moves_buffer)) {

    if (game.is_solved()) {
      LOGWARN("position is already solved");
      return Codes::solved_early();
    }

    LOGERROR("setup failed");
    return Codes::setup_failed();
  }

  return Codes::success();
}

bool Common::get_all_possible_moves(const Game& game,
    std::vector<Move>& possible_moves) {

  std::vector<Move> moves_buffer;

  if (!game.get_root_board().get_possible_moves(moves_buffer, true)) {
    LOGERROR("get possible moves failed");
    return false;
  }

  possible_moves.clear();

  std::transform(moves_buffer.begin(), moves_buffer.end(),
      std::back_inserter(possible_moves),
      [](const Move& move) {
    LOGDEBUG("possible move: ", move.to_string());
    return move;
  });

  return true;
}

void Common::transform_moves(const std::shared_ptr<WorkI>& work,
    std::vector<std::pair<uint16_t, uint16_t>>& results) {

  const Game& game(static_cast<const Game&>(*work.get()));

  std::vector<Move> moves;

  game.get_final_moves(moves);

  for (const Move& move : moves) {
    results.push_back( {move.get_index(), move.get_value()} );
  }
}

std::string Common::get_worker_load_summary() {

  std::shared_ptr<Router> router(Router::get_router());

  thread_local static std::vector<std::pair<uint16_t, uint16_t>> worker_pool_loads;

  worker_pool_loads.clear();

  router->get_worker_pool_loads(worker_pool_loads);

  std::ostringstream os;

  os << "worker loads: ";

  for (const auto& worker_pool_load : worker_pool_loads) {

    os << std::endl
        << "pool "
        << std::setfill('0')
        << std::setw(3)
        << worker_pool_load.first
        << "["
        << static_cast<const void*>(&worker_pool_load)
        << "]"
        << " load "
        << worker_pool_load.second;
  }

  return os.str();
}

}
}
}
}
