#include <vector>
#include <utility>
#include <tuple>

#include "sudoku_globals.h"
#include "sudoku_log.h"
#include "sudoku_node.h"
#include "sudoku_types.h"
#include "sudoku_workerpool.h"

namespace cc {
namespace tools {
namespace sudoku {

AtomicCounterU64Relaxed Node::_node_ids(1);

Node::Node(std::unique_ptr<Board> board,
    uint64_t game_id) :
		    _game_id(game_id),
		    _node_id(_node_ids.increment()),
		    _board(board.release()),
		    _child_node(),
		    _solved() {
}

bool Node::do_move_on_node_setup(const Move& move) {

  if (!_board->do_move_on_board(move)) {
    return false;
  }

  _board.reset(new Board(*(_board.get())));

  if (_board->is_solved()) {
    this->set_solved();
  }

  return true;
}

uint16_t Node::do_depth_first_search(Node *node,
    int64_t start_time,
    bool full_analysis) {

  LOGTRACE("entered at depth ", node->get_depth());

  if ((Clocks::steady_clock_now_MS() - start_time) > C_NODE_DFS_CODE_TIMEOUT_LIMIT) {
    return C_NODE_DFS_CODE_TIMEOUT;
  }

  if (Globals::is_exit_all_global()) {
    return C_NODE_DFS_FORCED_EXIT;
  }

  std::vector<Move> possible_moves;

  if (!node->_board->get_possible_moves(possible_moves, false)) {
    LOGTRACE("could not get moves");
    return C_NODE_DFS_CODE_NO_SOLUTION;
  }

  std::ostringstream os;

  for (const auto& possible_move : possible_moves) {
    if (!os.str().empty()) {
      os << ", ";
    }
    os << possible_move.to_string();
  }

  LOGTRACE("got ",
      possible_moves.size(),
      " possible moves: [",
      os.str(),
      "]");

  for (uint16_t i(0); i < possible_moves.size(); ++i) {

    if ((Clocks::steady_clock_now_MS() - start_time) > C_NODE_DFS_CODE_TIMEOUT_LIMIT) {
      return C_NODE_DFS_CODE_TIMEOUT;
    }

    if (Globals::is_exit_all_global()) {
      return C_NODE_DFS_FORCED_EXIT;
    }

    const Move& possible_move(possible_moves[i]);

    LOGTRACE("trying move at depth ",
        node->get_depth(),
        " move ",
        (i+1),
        "/",
        possible_moves.size());

    std::unique_ptr<Node> child_node(
        new Node(std::unique_ptr<Board>(new Board(node->get_board())),
            _game_id));

    if (full_analysis) {
      child_node->do_hidden_n_adjustment();
    }

    LOGTRACE("child depth increased by clone at depth ",
        node->get_depth(),
        " to depth ",
        child_node->get_depth(),
        " move ",
        (i+1),
        "/",
        possible_moves.size());

    if (child_node->do_move_on_node(possible_move)) {

      LOGTRACE("move ok at depth ",
          node->get_depth(),
          " move ",
          (i+1),
          "/",
          possible_moves.size(),
          " ",
          possible_move.to_string());

      LOGTRACE("moved node: ", child_node->to_string(true));

      if (child_node->is_board_solved()) {

        LOGTRACE("up[board solved] depth ",
            node->get_depth(),
            ".",
            (i + 1),
            "/",
            possible_moves.size());

        node->set_child_node(child_node);

        node->set_solved();

        return C_NODE_DFS_CODE_OK;
      }

      LOGTRACE("descending");

      uint16_t result(do_depth_first_search(child_node.get(),
          start_time,
          full_analysis));

      if (result == C_NODE_DFS_CODE_TIMEOUT) {

        LOGTRACE("up[timeout] depth ",
            node->get_depth(),
            ".",
            (i + 1),
            "/",
            possible_moves.size());

        return C_NODE_DFS_CODE_TIMEOUT;
      }

      if (result == C_NODE_DFS_FORCED_EXIT) {

        LOGTRACE("up[forced exit] depth ",
            node->get_depth(),
            ".",
            (i + 1),
            "/",
            possible_moves.size());

        return C_NODE_DFS_FORCED_EXIT;
      }

      if (result == C_NODE_DFS_CODE_OK) {

        if (child_node->is_solved()) {

          node->set_child_node(child_node);

          node->set_solved();

          LOGTRACE("up[board solved] depth ",
              node->get_depth(),
              ".",
              (i + 1),
              "/",
              possible_moves.size());

          return C_NODE_DFS_CODE_OK;
        }
      }
    } else {

      LOGTRACE("failed move at depth ",
          node->get_depth(),
          " move ",
          (i+1),
          "/",
          possible_moves.size());
    }
  }

  LOGTRACE("up[options exhausted] at depth ",
      node->get_depth());

  return C_NODE_DFS_CODE_NO_SOLUTION;
}

std::string Node::to_string(bool include_header) const {

  if (this->_child_node.get()) {

    return _child_node->to_string(include_header);

  } else {
    std::ostringstream os;

    if (include_header) {
      os << " game id:       "
          << _game_id
          << std::endl;
    }

    os << " node id:       "
        << _node_id
        << std::endl
        << " node address:  "
        << (reinterpret_cast<const void*>(this))
        << std::endl
        << _board->to_string();

    return os.str();
  }
}

}
}
}
