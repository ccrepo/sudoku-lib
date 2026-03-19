#include <cassert>
#include <sstream>

#include "sudoku_lib_setup_board.h"

#include "sudoku_log.h"
#include "sudoku_maths.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

SetupBoard::SetupBoard(const Board& board) : Board(board),
    _masks(),
    _indexes(),
    _remove_limit(generate_remove_limit()),
    _shuffle_limit(generate_shuffle_limit()),
    _remove_count(0),
    _shuffle_count(0),
    _valid(false) {

  if (board.is_moved_failed()) {
    return;
  }

  if (!board.is_solved()) {
    return;
  }

  for (uint16_t i(0); i<Geometry::C_GEOMETRY_TOTAL_CELLS; ++i) {

    uint16_t value(get_cells().get_cell(i).get_value());

    int32_t mask_index(value_index_to_mask_index(i));

    if (!is_value_valid(value) ||
        !is_mask_index_valid(mask_index)) {
      return;
    }

    _masks[mask_index].do_remove_matches(bits::_masks[value-1]);

    _indexes[mask_index] = i;
  }

  _valid = true;
}

std::string SetupBoard::to_string() const {

  std::ostringstream os;

  os << static_cast<const Board*>(this)->to_string();

  os << std::endl
      << " remove count:  "
      << _remove_count
      << "/"
      << _remove_limit
      << std::endl
      << " shuffle count: "
      << _shuffle_count
      << "/"
      << _shuffle_limit
      << std::endl
      << " valid:         "
      << (_valid ? "yes" : "no")
      << std::endl;

  for (uint16_t i(0); i<Geometry::C_GEOMETRY_TOTAL_CELLS; ++i) {

    if (!(i % Geometry::C_GEOMETRY_BOARD_SIZE)) {
      os << std::endl;
    }

    auto mask_index(value_index_to_mask_index(i));

    os << " "
        << std::setfill('0')
        << std::setw(2)
        << i
        << "|"
        << get_cells().get_cell(i).get_value()
        << "|"
        << std::setfill('0')
        << std::setw(2)
        << mask_index
        << "/"
        << std::setfill(' ')
        << std::setw((Location::C_LOCATION_MOVE_MAX - Location::C_LOCATION_MOVE_MIN) + 1)
        << mask_index_to_string(mask_index)
        << "[";

    if (is_mask_index_valid(mask_index)) {
      os << std::setfill('0')
          << std::setw(2)
          << _indexes[mask_index];
    } else {
      os << "  ";
    }

    os << "]";
  }

  os << std::endl;

  return os.str();
}

int32_t SetupBoard::value_index_to_mask_index(uint16_t value_index) const {

  if (value_index >= Geometry::C_GEOMETRY_TOTAL_CELLS) {
    return -1;
  }

  uint16_t value(get_cells().get_cell(value_index).get_value());

  if (!is_value_valid(value)) {
    return -1;
  }

  return (Geometry::index_to_block(value_index)*
      Geometry::C_GEOMETRY_BOARD_SIZE) + (value-1);
}

std::string SetupBoard::mask_index_to_string(int32_t mask_index) const {

  if (!is_mask_index_valid(mask_index)) {
    return "         ";
  }

  return _masks[mask_index].to_string();
}

bool SetupBoard::do_setup() {

  //Geometry::E_ROW_OR_COL get_rand_row_or_col() const {
  //  return static_cast<Geometry::E_ROW_OR_COL>(Maths::rand_in_range(0, 1));
  //}

  //inline uint16_t get_rand_block() const {
  //}

  return false;
}

}
}
}
}
