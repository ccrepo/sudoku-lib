#include "sudoku_index.h"

namespace cc {
namespace tools {
namespace sudoku {

std::string Index::to_string() const {

  std::ostringstream os;

  if (_index == USHRT_MAX) {
    return std::string("(-,-)");
  }

  os << _index
      << "("
      << get_row()
      << ","
      << get_col()
      << ")";

  return os.str();
}

bool Index::is_in_same_block(const std::vector<Index>& index_list) {

  if (index_list.size() < 2) {
    return true;
  }

  auto block_id(Geometry::index_to_block(index_list[0].get_index()));

  return std::all_of(index_list.begin() + 1, index_list.end(),
      [block_id](const Index& index) {

    return block_id == Geometry::index_to_block(index.get_index());

  } );
}

bool Index::is_in_same_col(const std::vector<Index>& index_list) {

  if (index_list.size() < 2) {
    return true;
  }

  auto col_id(Geometry::index_to_col(index_list[0].get_index()));

  return std::all_of(index_list.begin() + 1, index_list.end(),
      [col_id](const Index& index) {

    return col_id == Geometry::index_to_col(index.get_index());

  } );
}

bool Index::is_in_same_row(const std::vector<Index>& index_list) {

  if (index_list.size() < 2) {
    return true;
  }

  auto row_id(Geometry::index_to_row(index_list[0].get_index()));

  return std::all_of(index_list.begin() + 1, index_list.end(),
      [row_id](const Index& index) {

    return row_id == Geometry::index_to_row(index.get_index());

  } );
}

}
}
}
