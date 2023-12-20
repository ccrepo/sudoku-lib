#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <sstream>
#include <memory>
#include <vector>

#include "sudoku_types.h"
#include "sudoku_log.h"
#include "sudoku_move.h"
#include "sudoku_workI.h"
#include "sudoku_tree.h"
#include "sudoku_atomic_flag.h"
#include "sudoku_atomic_counter.h"

namespace cc {
namespace tools {
namespace sudoku {

class Game final : public WorkI {

public:
  explicit Game();

  explicit Game(std::unique_ptr<Board> board);

  virtual ~Game() override {
    LOGTRACE("destroying ", reinterpret_cast<void*>(this));
  }

public:
  virtual bool do_lock() override {
    return _is_locked_flag.test_and_set();
  }

  bool do_setup(const std::vector<Move>& moves,
      bool solved_position);

  virtual bool do_solve() override;

public:
  inline bool get_final_moves(std::vector<Move>& moves) const {
    return _tree->get_final_moves(moves);
  }

  inline bool get_final_positions(std::vector<Move>& moves) const {
    return _tree->get_final_positions(moves);
  }

  inline uint64_t get_game_id() const {
    return _game_id;
  }

  virtual std::function<void ()> get_autocall_callback_lambda() override {
    return [this]() {
       this->set_is_interrupted();
    };
  }

  inline const Board& get_root_board() const {
    return _tree->get_root_board();
  }

public:
  inline bool has_root_board() const {
    return _tree->has_root_board();
  }

public:
  virtual bool is_interrupted() const override {
    return _is_interrupted.test();
  }

  virtual bool is_locked() const override {
    return _is_locked_flag.test();
  }

  virtual bool is_processed() const override {
    return _is_processed_flag.test();
  }

  virtual bool is_solved() const override {
    return _tree->is_solved();
  }

  virtual bool is_timeout() const override {
    return _tree->is_timeout();
  }

public:
  virtual void set_is_processed() override {
    _is_processed_flag.set();
  }

  virtual void set_is_interrupted() override {
    _is_interrupted.set();
  }

public:
  std::string to_string() const;

private:
  const uint64_t _game_id;

  std::shared_ptr<Tree> _tree;

private:
  AtomicFlagSemiRelaxed _is_interrupted;

  AtomicFlagRelAcq _is_locked_flag;

  AtomicFlagSemiRelaxed _is_processed_flag;

private:
  static AtomicCounterU64Relaxed _game_ids;

private:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

};

}
}
}

#endif
