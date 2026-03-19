#include "sudoku_tree.h"

namespace cc {
namespace tools {
namespace sudoku {

Tree::Tree(uint64_t game_id) :
			    Node(std::unique_ptr<Board>(new Board()), game_id),
			    _timeout() {
}

Tree::Tree(std::unique_ptr<Board>& board,
    uint64_t game_id) :
			    Node(std::unique_ptr<Board>(board.release()), game_id),
			    _timeout() {
}

bool Tree::do_solve(bool full_analysis) {
  LOGTRACE("start solve");

  if (this->is_board_solved()) {
    LOGTRACE("board already solved");
    return true;
  }

  auto start_time(Clocks::steady_clock_now_MS());

  uint16_t result(do_depth_first_search(this,
      start_time,
      full_analysis));

  if (result == C_NODE_DFS_CODE_OK) {
    LOGTRACE("end solve (ok)");
    return true;
  }

  if (result == C_NODE_DFS_FORCED_EXIT) {
    LOGTRACE("end solve (forced exit)");
    return false;
  }

  if (result == C_NODE_DFS_CODE_NO_SOLUTION) {
    LOGTRACE("end solve (no solution)");
    return false;
  }

  if (result == C_NODE_DFS_CODE_TIMEOUT) {

    if (full_analysis) {
      LOGTRACE("end solve (timeout full analysis)");
      _timeout.set();
      return false;
    }

    LOGTRACE("timeout so replay do solve");
    return do_solve(true);
  }

  return false;
}

}
}
}
