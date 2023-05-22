#include "sudoku_game.h"

namespace cc {
namespace tools {
namespace sudoku {

std::atomic<uint64_t> Game::_game_ids(0);

bool Game::do_setup(const std::vector<Move>& moves) {

  if (_tree->get_root_board().is_solved()) {
    LOGERROR("already solved");

    return false;
  }

  if (_tree->get_root_board().is_invalid()) {
    LOGERROR("already invalid");

    return false;
  }

  for (const auto& move : moves) {

    if (!_tree->do_setup_move(move)) {

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

    if (_tree->get_root_board().is_solved()) {

      LOGINFO("move ",
          move.to_string(),
          " solved game");

      return false;
    }

    if (_tree->get_root_board().is_invalid()) {

      LOGINFO("move ",
          move.to_string(),
          " invalidated game");

      return false;
    }
  }

  return true;
}

Game::Game() :
	    WorkI(),
	    _game_id(++_game_ids),
	    _tree(new Tree(_game_id)),
	    _is_interrupted(false),
	    _is_locked(false),
	    _is_processed(false) {
}

Game::Game(std::unique_ptr<Board> board) :
      WorkI(),
	    _game_id(++_game_ids),
	    _tree(new Tree(board, _game_id)),
	    _is_interrupted(false),
	    _is_locked(false),
	    _is_processed(false) {
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
