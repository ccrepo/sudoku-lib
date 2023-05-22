#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <sstream>
#include <array>
#include <vector>
#include <atomic>
#include <tuple>
#include <algorithm>

#include "sudoku_cellset.h"
#include "sudoku_log.h"
#include "sudoku_move.h"
#include "sudoku_mask.h"

namespace cc {
namespace tools {
namespace sudoku {

class Board final {
public:
  Board();

  virtual ~Board() {
  }

  explicit Board(const Board& board);

public:
  bool do_move(const Move& move);

  bool do_hidden_n_adjustment();

public:
  bool check_solved() const;

public:
  inline bool get_all_moves(std::vector<Move>& moves) const {
    moves = _previous_moves;
    return true;
  }

  bool get_all_positions(std::vector<Move>& moves) const;

  inline uint64_t get_depth() const {
    return _depth;
  }

  inline uint64_t get_board_id() const {
    return _board_id;
  }

  const Move& get_last_move() const {
    return _previous_moves[_previous_moves.size()-1];
  }

  bool get_possible_moves(std::vector<Move>& buffer,
      bool return_all) const;

  std::vector<std::pair<uint16_t, std::shared_ptr<std::vector<Index>>>> get_adjust_index_lists_n(
      const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& check_region,
      uint16_t n);

public:
  bool has_move() const {
    return _previous_moves.size();
  }

public:
  inline bool is_invalid() const {
    return _invalid;
  }

  bool is_move_possible(const Move& move) const;

  inline bool is_solved() const {
    return _solved;
  }

public:
  std::string to_string(bool include_header = false) const;

private:
  bool do_hidden_n_adjustment_block(uint16_t size);

  bool do_hidden_n_adjustment_col(uint16_t size);

  bool do_hidden_n_adjustment_row(uint16_t size);

  uint16_t update_hidden_n(Geometry::E_REGION_TYPE region_type,
      const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& check_region,
      uint16_t size);

private:
  static std::atomic<uint64_t> _board_ids;

private:
  const uint64_t _board_id;

  const uint64_t _parent_board_id;

  const uint64_t _depth;

  CellSet _cells;

  bool _invalid;

  bool _solved;

  std::vector<Move> _previous_moves;

private:
  static constexpr int64_t C_BOARD_HIDDEN_N_ADJUST_LIMIT { 81 + 1 };
  static constexpr std::array<uint16_t, 3> C_BOARD_HIDDEN_N_SIZES { 4, 3, 2 };

private:
  Board& operator=(const Board&) = delete;

};

}
}
}

#endif
