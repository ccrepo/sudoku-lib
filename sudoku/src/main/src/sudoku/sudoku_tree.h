#ifndef SUDOKU_TREE_H
#define SUDOKU_TREE_H

#include <sstream>
#include <memory>

#include "sudoku_board.h"
#include "sudoku_node.h"
#include "sudoku_clocks.h"

namespace cc {
namespace tools {
namespace sudoku {

class Tree final : public Node, std::enable_shared_from_this<Tree> {

public:
  explicit Tree(uint64_t game_id);

  explicit Tree(std::unique_ptr<Board>& board,
      uint64_t game_id);

  virtual ~Tree() override {
  }

public:

  bool do_solve(bool full_analysis);

public:
  inline const Board& get_root_board() const {
    return Node::get_board();
  }

  inline bool has_root_board() const {
    return Node::has_board();
  }

  inline bool is_timeout() const {
    return _timeout.test();
  }

private:
  AtomicFlagRelAcq _timeout;

private:
  Tree(const Tree&) = delete;
  Tree& operator=(const Tree&) = delete;

};

}
}
}

#endif
