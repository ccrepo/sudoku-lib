#include "sudoku_game.h"

namespace cc {
namespace tools {
namespace sudoku {

AtomicCounterU64Relaxed Game::_game_ids(1);

bool Game::do_setup(const std::vector<Move>& moves,
    bool solved_position) {

  if (_tree->get_root_board().is_solved()) {
    LOGERROR("already solved");

    return false;
  }

  for (const auto& move : moves) {

    if (!_tree->do_move_on_node_setup(move)) {

      LOGDEBUG("move ",
          move.to_string(),
          " failed");

      return false;
    }

    LOGDEBUG("move ", move.to_string(), " ok");

    LOGTRACE("game delta ",
        this->get_game_id(),
        ": ",
        this->to_string());

    if (!solved_position &&
        _tree->get_root_board().is_solved()) {

      LOGWARN("move ",
          move.to_string(),
          " solved game");

      return false;
    }
  }

  if (solved_position &&
      !_tree->get_root_board().is_solved()) {

    LOGERROR("game is not solved");

    return false;
  }

  return true;
}

Game::Game() :
	    WorkI(),
	    _game_id(_game_ids.increment()),
	    _tree(new Tree(_game_id)),
	    _is_interrupted(),
	    _is_locked_flag(),
	    _is_processed_flag() {
}

Game::Game(std::unique_ptr<Board> board) :
      WorkI(),
	    _game_id(_game_ids.increment()),
	    _tree(new Tree(board, _game_id)),
	    _is_interrupted(),
	    _is_locked_flag(),
	    _is_processed_flag() {
}

std::string Game::to_string() const {
  std::ostringstream os;

  os << std::endl
      << std::endl
      << " game id:       "
      << _game_id
      << std::endl
      << " game address:  "
      << (reinterpret_cast<const void*>(this))
      << std::endl
      << _tree->to_string();

  return os.str();
}

bool Game::do_solve() {
  if (_tree.get()) {
    return _tree->do_solve(false);
  }

  return false;
}

}
}
}
