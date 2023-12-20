#include <functional>
#include <algorithm>
#include <cstring>
#include <set>

#include "sudoku_board.h"
#include "sudoku_regions.h"
#include "sudoku_config.h"
#include "sudoku_log.h"
#include "sudoku_geometry.h"
#include "sudoku_bitpermutation.h"

namespace cc {
namespace tools {
namespace sudoku {

AtomicCounterU64Relaxed Board::_board_ids(1);

std::string Board::to_string(bool include_header [[maybe_unused]]) const {

  static const bool is_higher_level_logging(
      Config::get_config()->is_log_all() ||
      Config::get_config()->is_log_trace() ||
      Config::get_config()->is_log_debug() //||
      //Config::get_config()->is_log_info() ||
      //Config::get_config()->is_no_level()
      );

  std::ostringstream os;

  os << " board id:      "
      << this->_board_id
      << std::endl
      << " board address: "
      << (reinterpret_cast<const void*>(this))
      << std::endl
      << " move count:    "
      << _previous_moves.size()
      << std::endl
      << " move info:     ";

  if (!_previous_moves.empty()) {
    os << _previous_moves[_previous_moves.size()-1].to_string();
  } else {
    os << "-";
  }

  os << std::endl
      << " parent board:  "
      << this->_parent_board_id << std::endl
      << " depth:         "
      << this->_depth
      << std::endl
      << " solved:        "
      << (is_solved() ? "yes" : "no")
      << std::endl
      << _cells.to_string();

  if (is_higher_level_logging) {
    os << std::endl
        << _cells.to_string(is_higher_level_logging);
  }

  os << std::endl
      << std::endl
      << " ["
      << std::endl;

  if (!_previous_moves.empty()) {
    size_t i(0);

    for (const Move& move : _previous_moves) {

      os << " ["
          << ++i
          << "] "
          << move.to_string()
          << std::endl;
    }
  }

  os << " ]";

  if (is_higher_level_logging) {

    os << std::endl
        << std::endl
        << " [ ";

    for (size_t i(0); i < _cells.get_size(); ++i) {

      const auto& cell(_cells.get_cells()[i]);

      if (cell.is_moves_exist()) {

        os << std::setfill('0')
            << std::setw(2)
            << i
            << " ";
      }
    }

    os << "]"
        << std::endl;
  }

  return os.str();
}

bool Board::check_solved() const {

  if (!_cells.check_solved()) {
    LOGTRACE("solved no");
    return false;
  }

  LOGTRACE("solved yes");
  return true;
}

bool Board::do_move_on_board(const Move& move) {

  if (is_moved_failed()) {
    LOGWARN("is already move failed");
    return false;
  }

  if (is_solved()) {
    LOGWARN("is already solved");
    return false;
  }

  LOGTRACE("checking move ", move.to_string());

  if (!is_move_possible(move)) {
    LOGTRACE("move not possible");
    return false;
  }

  LOGTRACE("doing move ", move.to_string());

  if (!_cells.do_move_on_cellset(move)) {
    LOGTRACE("move failed");
    return false;
  }

  if(check_solved()) {
    LOGTRACE("board solved");
    _solved = true;
  } else {
    LOGTRACE("board not solved");
    _solved = false;
  }

  _previous_moves.push_back(move);

  return true;
}

bool Board::get_possible_moves(std::vector<Move>& buffer,
    bool return_all) const {

  if (!_cells.get_possible_moves(buffer, return_all)) {
    return false;
  }

  return true;
}

bool Board::is_move_possible(const Move& move) const {

  if (!_cells.is_move_possible(move)) {
    LOGTRACE("move not possible ", move.to_string());
    return false;
  }

  return true;
}

bool Board::do_hidden_n_adjustment() {

  LOGTRACE("start hidden n adjustment");

  bool r(false);

  uint16_t counter(C_BOARD_HIDDEN_N_ADJUST_LIMIT);

  for (uint16_t size : C_BOARD_HIDDEN_N_SIZES ) {

    LOGTRACE("doing adjust for size ", size);

    while (--counter) {

      r = false;

      r = do_hidden_n_adjustment_block(size) || r;
      r = do_hidden_n_adjustment_col(size) || r;
      r = do_hidden_n_adjustment_row(size) || r;

      if (!r) {
        break;
      }

      LOGTRACE("retrying");
    }
  }

  LOGTRACE("finished");

  return r;
}

bool Board::do_hidden_n_adjustment_block(uint16_t size) {

  static const auto blocks(Regions::get_regions()->get_blocks());

  bool r(false);

  for (const auto& block : blocks) {
    r = static_cast<bool>(update_hidden_n(Geometry::E_REGION_TYPE_BLOCK,
        block,
        size)) || r;
  }

  return r;
}

bool Board::do_hidden_n_adjustment_col(uint16_t size) {
  static const auto cols(Regions::get_regions()->get_cols());

  bool r(false);

  for (const auto& col : cols) {
    r = static_cast<bool>(update_hidden_n(Geometry::E_REGION_TYPE_COL,
        col,
        size)) || r;
  }

  return r;
}

bool Board::do_hidden_n_adjustment_row(uint16_t size) {
  static const auto rows(Regions::get_regions()->get_rows());

  bool r(false);

  for (const auto& row : rows) {
    r = static_cast<bool>(update_hidden_n(Geometry::E_REGION_TYPE_ROW,
        row,
        size)) || r;
  }

  return r;
}

std::vector<std::pair<uint16_t, std::shared_ptr<std::vector<Index>>>> Board::get_adjust_index_lists_n(
    const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& check_region,
    uint16_t n) {

  std::vector<std::pair<uint16_t, std::shared_ptr<std::vector<Index>>>> results;

  if (n < 2) {
    return results;
  }

  typedef std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> rcb_list;

  rcb_list cell_value_totals { };
  rcb_list cell_value_total_totals { };
  rcb_list cell_values_bits { };

  std::set<uint16_t> cell_values_of_size;

  for (uint16_t i(0); i < check_region.size(); ++i) {

    for (auto cell_value : Cell::C_CELL_VALUES) {

      if ((_cells.get_cells()[check_region[i]]).
          is_move_exists(cell_value)) {

        cell_value_totals[cell_value-1] += 1;

        cell_values_bits[i] += bits::_masks[cell_value-1];

        if (cell_value_totals[cell_value-1] == n) {
          cell_values_of_size.insert(cell_value-1);

        } else if (cell_value_totals[cell_value-1] > n) {
          cell_values_of_size.erase(cell_value-1);

        }
      }
    }
  }

  if (cell_values_of_size.empty()) {
    return results;
  }

  for (auto cell_value_total :
      cell_value_totals) {
    cell_value_total_totals[cell_value_total-1] += 1;
  }

  if (cell_value_total_totals[n - 1] < n) {
    return results;
  }

  uint16_t control_bits(0);

  for (auto cell_value_of_size : cell_values_of_size) {
    control_bits =
        control_bits ^ bits::_masks[cell_value_of_size];
  }

  for (auto bitpermutation : BitPermutation::get_bitpermutation_n(n)) {

    std::shared_ptr<std::vector<Index>> result(new std::vector<Index>());

    for (uint16_t k(0); k < cell_values_bits.size(); ++k) {

      auto cell_value_bits(cell_values_bits[k]);

      if ((cell_value_bits &
          control_bits &
          bitpermutation) == bitpermutation) {

        result->push_back(
            Index(check_region[k]));
      }
    }

    if (result->size() == n) {
      results.push_back(
          std::make_pair(bitpermutation, result));
    }
  }

  return results;
}

uint16_t Board::update_hidden_n(Geometry::E_REGION_TYPE region_type,
    const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& check_region,
    uint16_t n) {

  static const bool is_trace_level_logging(
      Config::get_config()->is_log_trace());

  LOGTRACE("start ",
      this->to_string(true));

  std::vector<std::pair<uint16_t, std::shared_ptr<std::vector<Index>>>>
  adjust_index_lists(get_adjust_index_lists_n(check_region, n));

  std::weak_ptr<Regions> weak(Regions::get_regions());

  std::shared_ptr<Regions> regions(weak.lock());

  if (!regions) {
    return 0;
  }

  for (auto& adjust_index_list : adjust_index_lists) {

    if (is_trace_level_logging) {

      std::ostringstream os;

      os << adjust_index_list.first
          << '(';

      for (const Index& adjust_index : *(adjust_index_list.second)) {
        os << adjust_index.get_index()
				  << " ";
      }

      os << ')';

      LOGTRACE("adjust moves: ", os.str());
    }

    if (adjust_index_list.second->empty()) {
      continue;
    }

    const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>* update_indexes(nullptr);

    if (region_type == Geometry::E_REGION_TYPE_BLOCK) {

      if (Index::is_in_same_row(*(adjust_index_list.second))) {

        update_indexes = &regions->get_row(
            Geometry::index_to_row(
                (adjust_index_list.second->operator[](0)).get_index()));

      } else if (Index::is_in_same_col(*(adjust_index_list.second))) {

        update_indexes = &regions->get_col(
            Geometry::index_to_col(
                (adjust_index_list.second->operator[](0)).get_index()));
      }

    } else if (region_type == Geometry::E_REGION_TYPE_COL ||
        region_type == Geometry::E_REGION_TYPE_ROW) {

      if (Index::is_in_same_block(*(adjust_index_list.second))) {

        update_indexes = &regions->get_block(
            Geometry::index_to_block(
                (adjust_index_list.second->operator[](0)).get_index()));
      }

    } else {
      return 0;
    }

    if (update_indexes == nullptr) {
      continue;
    }

    uint16_t updated_count(0);

    for (uint16_t update_index : (*update_indexes)) {

      if (std::find(
          adjust_index_list.second->begin(),
          adjust_index_list.second->end(),
          update_index) != adjust_index_list.second->end()) {

        LOGTRACE("keep matches as in n-set ", update_index);

        Cell& cell(_cells.get_cell(update_index));

        uint16_t pre_number_potential_moves(cell.get_number_potential_moves());

        if (pre_number_potential_moves) {
          cell.do_keep_matches(adjust_index_list.first);

          updated_count += pre_number_potential_moves -
              cell.get_number_potential_moves();
        }
      } else {

        LOGTRACE("remove matches as not in n-set ", update_index);

        Cell& cell(_cells.get_cell(update_index));

        uint16_t pre_number_potential_moves(cell.get_number_potential_moves());

        if (pre_number_potential_moves) {
          cell.do_remove_matches(adjust_index_list.first);

          updated_count += pre_number_potential_moves -
              cell.get_number_potential_moves();
        }
      }
    }

    if (updated_count) {
      return updated_count;
    }
  }

  return 0;
}

Board::Board(const Board& board) :
        _board_id(_board_ids.increment()),
		    _parent_board_id(board._board_id),
		    _depth(board._depth + 1),
		    _cells(board._cells),
		    _solved(board._solved),
		    _moved_failed(board._moved_failed),
		    _previous_moves(board._previous_moves) {

  LOGTRACE("copy constructor board ",
      _board_id,
      " from ",
      board._board_id);
}

Board::Board() : _board_id(_board_ids.increment()),
		    _parent_board_id(0),
		    _depth(1),
		    _cells { },
		    _solved(false),
		    _moved_failed(false),
		    _previous_moves() {

	LOGTRACE("default constructor board ", _board_id);
}

bool Board::get_all_positions(std::vector<Move>& moves) const {

  for (size_t i(0); i < _cells.get_size(); ++i) {

    const auto& cell(_cells.get_cells()[i]);

    moves.push_back(Move(i, cell.get_value(), 0));
  }

  return true;
}

}
}
}
