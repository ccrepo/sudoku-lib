#include "sudoku_mask.h"

namespace cc {
namespace tools {
namespace sudoku {

bool Mask::do_keep_matches(uint16_t bitmask) {

  bool result(false);

  for (uint16_t i(0); i < mask::C_MASK_NUM_ELEMENTS; ++i) {

    if (!(get_data()[i] && (bitmask & bits::_masks[i]))) {

      if (get_data()[i]) {

        set_data(i,
            static_cast<unsigned char>(0));

        result = true;
      }
    }
  }

  return result;
}

bool Mask::do_remove_matches(uint16_t bitmask) {

  bool result(false);

  for (uint16_t i(0); i < mask::C_MASK_NUM_ELEMENTS; ++i) {

    if (get_data()[i] &&
        (bitmask & bits::_masks[i])) {

      set_data(i,
          static_cast<unsigned char>(0));

      result = true;
    }
  }

  return result;
}

bool Mask::can_adjust(uint16_t cell_value,
    uint16_t play_value) const {

  if (!is_valid_play_value(play_value)) {
    return false;
  }

  if (!is_moves_exist()) {
    return cell_value != play_value;
  }

  return is_moves_exist_adjusted(play_value);
}

bool Mask::can_move(uint16_t play_value) const {

  if (!is_valid_play_value(play_value)) {
    return false;
  }

  if (is_move_exists(play_value)) {
    return true;
  }

  return false;
}

bool Mask::do_adjust(uint16_t value) {

  for (uint16_t i(0); i<mask::C_MASK_NUM_ELEMENTS; ++i) {

    if (get_data()[i] && ((value-1) == i)) {

      set_data(i,
          static_cast<unsigned char>(0));
    }
  }

  return true;
}

bool Mask::do_move_on_mask() {

  for (uint16_t i(0); i<mask::C_MASK_NUM_ELEMENTS; ++i) {

    if (get_data()[i]) {
      set_data(i,
          static_cast<unsigned char>(0));
    }
  }

  return true;
}

uint16_t Mask::get_index_potential_move() const {

  for (uint16_t i(0); i<mask::C_MASK_NUM_ELEMENTS; ++i) {

    if (get_data()[i]) {
      return i;
    }
  }

  throw std::out_of_range ("no match");
}

uint16_t Mask::get_number_potential_moves() const {

  return static_cast<bool>(get_data()[0]) +
      static_cast<bool>(get_data()[1]) +
      static_cast<bool>(get_data()[2]) +
      static_cast<bool>(get_data()[3]) +
      static_cast<bool>(get_data()[4]) +
      static_cast<bool>(get_data()[5]) +
      static_cast<bool>(get_data()[6]) +
      static_cast<bool>(get_data()[7]) +
      static_cast<bool>(get_data()[8]);
}

std::vector<uint16_t> Mask::get_potential_moves() const {
  std::vector<uint16_t> buffer;

  for (uint16_t i(0); i < mask::C_MASK_NUM_ELEMENTS; ++i) {

    if (get_data()[i]) {
      buffer.push_back(i+1);
    }
  }

  return buffer;
}

uint16_t Mask::is_moves_exist() const {

  return static_cast<bool>(get_data()[0]) ||
      static_cast<bool>(get_data()[1]) ||
      static_cast<bool>(get_data()[2]) ||
      static_cast<bool>(get_data()[3]) ||
      static_cast<bool>(get_data()[4]) ||
      static_cast<bool>(get_data()[5]) ||
      static_cast<bool>(get_data()[6]) ||
      static_cast<bool>(get_data()[7]) ||
      static_cast<bool>(get_data()[8]);
}

uint16_t Mask::is_moves_exist_adjusted(uint16_t value) const {

  value = (value - 1);

  return (static_cast<bool>(get_data()[0]) && value != 0) ||
      (static_cast<bool>(get_data()[1]) && value != 1) ||
      (static_cast<bool>(get_data()[2]) && value != 2) ||
      (static_cast<bool>(get_data()[3]) && value != 3) ||
      (static_cast<bool>(get_data()[4]) && value != 4) ||
      (static_cast<bool>(get_data()[5]) && value != 5) ||
      (static_cast<bool>(get_data()[6]) && value != 6) ||
      (static_cast<bool>(get_data()[7]) && value != 7) ||
      (static_cast<bool>(get_data()[8]) && value != 8);
}

std::string Mask::to_string() const {

  std::ostringstream os;

  os << MaskT<mask::C_MASK_NUM_ELEMENTS>::to_string();

  return os.str();
}

}
}
}
