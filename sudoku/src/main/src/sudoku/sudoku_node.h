#ifndef SUDOKU_NODE_H
#define SUDOKU_NODE_H

#include <memory>
#include <vector>

#include "sudoku_types.h"
#include "sudoku_board.h"
#include "sudoku_atomic_flag.h"
#include "sudoku_atomic_counter.h"

namespace cc {
namespace tools {
namespace sudoku {

class Node {

public:
  virtual ~Node() {
  }

  std::string to_string(bool include_header = false) const;

  bool do_move_on_node_setup(const Move& move);

  inline bool get_final_moves(std::vector<Move>& moves) const {
    if (_child_node.get()) {
      return _child_node->get_final_moves(moves);
    }

    return _board->get_all_moves(moves);
  }

  inline bool get_final_positions(std::vector<Move>& moves) const {
    if (_child_node.get()) {
      return _child_node->get_final_positions(moves);
    }

    return _board->get_all_positions(moves);
  }

  inline uint64_t get_id() const {
    return _node_id;
  }

  inline bool is_board_solved() const {
    return _board->is_solved();
  }

  inline bool is_solved() const {
    return _solved.test();
  }

protected:
  explicit Node(std::unique_ptr<Board> board,
      uint64_t game_id);

public:
  static constexpr uint16_t C_NODE_DFS_CODE_OK { 0 };
  static constexpr uint16_t C_NODE_DFS_CODE_TIMEOUT { 1 };
  static constexpr uint16_t C_NODE_DFS_FORCED_EXIT { 2 };
  static constexpr uint16_t C_NODE_DFS_CODE_NO_SOLUTION { 3 };
  static constexpr int64_t C_NODE_DFS_CODE_TIMEOUT_LIMIT { 1000 };

protected:
  uint16_t do_depth_first_search(Node *node,
      int64_t start_time,
      bool full_analysis);

  inline const Board& get_board() const {
    return (*_board);
  }

  inline uint64_t get_depth() const {
    return _board->get_depth();
  }

  inline bool has_board() const {
    return _board.get();
  }

private:
  bool do_hidden_n_adjustment() {
    return _board->do_hidden_n_adjustment();
  }

  inline bool do_move_on_node(const Move& move) {
    return _board->do_move_on_board(move);
  }

private:
  inline void set_child_node(std::unique_ptr<Node>& child_node) {
    _child_node.swap(child_node);
  }

  inline void set_solved() {
    _solved.set();
  }

private:
  static AtomicCounterU64Relaxed _node_ids;

private:
  const uint64_t _game_id;

  const uint64_t _node_id;

private:
  std::unique_ptr<Board> _board;

  std::unique_ptr<Node> _child_node;

  AtomicFlagRelAcq _solved;

private:
  Node& operator=(const Node&) = delete;

};

}
}
}

#endif

