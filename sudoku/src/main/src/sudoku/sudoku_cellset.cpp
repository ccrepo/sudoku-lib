#include <algorithm>
#include <cstring>

#include "sudoku_cellset.h"
#include "sudoku_log.h"
#include "sudoku_move.h"
#include "sudoku_regions.h"

namespace cc {
namespace tools {
namespace sudoku {

bool CellSet::do_move_on_cellset(const Move& move) {

  if (!_cells[move.get_index()].do_move_on_cell(move)) {
    LOGTRACE("failed");

    return false;
  }

  std::weak_ptr<Regions> weak(Regions::get_regions());

  std::shared_ptr<Regions> regions(weak.lock());

  if (!regions) {
    return false;
  }

  const auto& block(regions->get_block
      (Geometry::index_to_block(move.get_index())));

  const auto& col(regions->get_col
      (Geometry::index_to_col(move.get_index())));

  const auto& row(regions->get_row
      (Geometry::index_to_row(move.get_index())));

  auto& cells(_cells);

  for (const auto& region : { block, col, row } ) {
    if (!std::all_of(region.begin(), region.end(), [&move, &cells](auto i) {

      if (i == move.get_index()) {
        return true;
      }
      return cells[i].do_adjust(move);
    })) {
      LOGTRACE("move cannot adjust row cell ", move.to_string());
      return false;
    }
  }

  LOGTRACE("move done ", move.to_string());
  return true;
}

bool CellSet::is_move_possible(const Move& move) const {

  if (_cells[move.get_index()].get_value()) {
    LOGERROR("move already played ", move.to_string());
    return false;
  }

  if (!_cells[move.get_index()].can_move(move)) {
    LOGTRACE("move in cell illegal ", move.to_string());
    return false;
  }

  std::weak_ptr<Regions> weak(Regions::get_regions());

  std::shared_ptr<Regions> regions(weak.lock());

  if (!regions) {
    return false;
  }

  const auto& block(regions->get_block
      (Geometry::index_to_block(move.get_index())));

  const auto& col(regions->get_col
      (Geometry::index_to_col(move.get_index())));

  const auto& row(regions->get_row
      (Geometry::index_to_row(move.get_index())));

  const auto& cells(_cells);

  for (const auto& region : { block, col, row } ) {
    if (!std::all_of(region.begin(), region.end(), [&move, &cells](auto i) {
      if (i == move.get_index()) {
        return true;
      }
      return cells[i].can_adjust(move);
    })) {
      LOGTRACE("move cannot adjust row cell ", move.to_string());
      return false;
    }
  }

  LOGTRACE("move is possible ", move.to_string());
  return true;
}

std::string CellSet::to_string(bool is_verbose) const {
  std::ostringstream os;

  for (uint16_t i(0); i < _cells.size(); ++i) {

    if (!(i % Geometry::C_GEOMETRY_BOARD_SIZE)) {
      os << " "
          << std::endl;
    }

    os << ' ';

    if (is_verbose) {
      os << std::setfill('0')
					    << std::setw(2)
					    << i
					    << '|';
    }

    os << _cells[i].to_string(is_verbose);
  }

  return os.str();
}

bool CellSet::check_solved() const {

  if (!std::all_of(_cells.begin(), _cells.end(), [](const auto& cell) {
    return cell.is_solved();
  })) {
    return false;
  }

  bool buffer[Location::C_LOCATION_MOVE_MAX];

  std::weak_ptr<Regions> weak(Regions::get_regions());

  std::shared_ptr<Regions> regions(weak.lock());

  if (!regions) {
    return false;
  }

  for (uint16_t i(0); i < Geometry::C_GEOMETRY_BOARD_SIZE; ++i) {

    const auto& block_i(regions->get_block
        (Geometry::index_to_block(i)));

    const auto& col_i(regions->get_col
        (Geometry::index_to_col(i)));

    const auto& row_i(regions->get_row
        (Geometry::index_to_row(i)));

    const auto& cells(_cells);

    for (const auto& region : { block_i, col_i, row_i } ) {
      memset(&buffer, 0, sizeof(buffer));

      if (!std::all_of(region.begin(), region.end(), [&cells, &buffer](uint16_t i) {
        auto value(cells[i].get_value());

        if (!value ||
            value > Location::C_LOCATION_MOVE_MAX ||
            buffer[value-1]) {
          return false;
        }
        buffer[value-1] = true;
        return true;
      })) {
        return false;
      }
    }
  }

  return true;
}

uint16_t CellSet::get_weight(uint16_t index, uint16_t value) const {

  auto number_potential_moves(_cells[index].get_number_potential_moves());

  if (number_potential_moves == 1) {
    return 1;
  }

  std::weak_ptr<Regions> weak(Regions::get_regions());

  std::shared_ptr<Regions> regions(weak.lock());

  if (!regions) {
    return false;
  }

  const auto& block(regions->get_block
      (Geometry::index_to_block(index)));

  const auto& col(regions->get_col
      (Geometry::index_to_col(index)));

  const auto& row(regions->get_row
      (Geometry::index_to_row(index)));

  const auto& cells(_cells);

  for (const auto& region : { block, col, row } ) {
    if (std::all_of(region.begin(), region.end(),
        [&cells, index, value](uint16_t i) {

      if (index == i) {
        return true;
      }

      if (!cells[i].get_value() &&
          cells[i].is_move_exists(value)) {
        return false;
      }

      return true;
    })) {
      return 2;
    }
  }

  return number_potential_moves * C_CELLSET_DETERMINSTIC_THRESHOLD;
}

bool CellSet::get_possible_moves(std::vector<Move>& buffer,
    bool return_all) const {

  std::vector<Move> possible_moves;

  for (uint16_t i(0); i < _cells.size(); ++i) {

    const Cell& cell(_cells[i]);

    if (!cell.get_value() &&
        cell.is_moves_exist()) {

      const std::vector<uint16_t>& potential_moves(
          cell.get_mask().get_potential_moves());

      if (!return_all &&
          potential_moves.size() == 1) {

        auto weight(get_weight(i, potential_moves[0]));

        buffer.push_back(Move(i, potential_moves[0], weight));

        return true;
      }

      for (uint16_t potential_move : potential_moves) {

        auto weight(get_weight(i, potential_move));

        if (!return_all &&
            weight <= C_CELLSET_DETERMINSTIC_THRESHOLD) {

          buffer.push_back(Move(i, potential_move, weight));

          return true;
        }

        possible_moves.push_back(Move(i, potential_move, weight));
      }
    }
  }

  if (possible_moves.empty()) {
    return true;
  }

  if (!return_all) {
    auto worker_pool_load = std::min_element(possible_moves.begin(), possible_moves.end());

    uint16_t index(worker_pool_load->get_index());

    std::copy_if(possible_moves.begin(), possible_moves.end(), std::back_inserter(buffer),
        [index](const auto& move) {
      return index == move.get_index();
    });
  } else {
    sort(possible_moves.begin(), possible_moves.end());

    std::copy(possible_moves.begin(), possible_moves.end(),
        std::back_inserter(buffer));
  }

  return true;
}

std::array<uint16_t, Geometry::C_GEOMETRY_TOTAL_CELLS> CellSet::get_values() const {
  std::array<uint16_t, Geometry::C_GEOMETRY_TOTAL_CELLS> values;

  for (uint16_t i(0); i < _cells.size(); ++i) {
    values[i] = _cells[i].get_value();
  }

  return values;
}

}
}
}
