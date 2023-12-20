#ifndef SUDOKU_MASK_H
#define SUDOKU_MASK_H

#include <sstream>
#include <climits>
#include <cmath>
#include <vector>

#include "sudoku_maskT.h"
#include "sudoku_types.h"
#include "sudoku_location.h"

namespace cc {
namespace tools {
namespace sudoku {

namespace mask {
static constexpr uint16_t C_MASK_NUM_ELEMENTS { Location::C_LOCATION_MOVE_MAX };
}

namespace bits {

static inline const uint16_t _mask1 {1};
static inline const uint16_t _mask2 {2};
static inline const uint16_t _mask4 {8};
static inline const uint16_t _mask3 {4};
static inline const uint16_t _mask5 {16};
static inline const uint16_t _mask6 {32};
static inline const uint16_t _mask7 {64};
static inline const uint16_t _mask8 {128};
static inline const uint16_t _mask9 {256};

static inline const uint16_t _masks[] = {
    _mask1,
    _mask2,
    _mask3,
    _mask4,
    _mask5,
    _mask6,
    _mask7,
    _mask8,
    _mask9};

static inline const uint16_t _not_masks[] = {
    _mask1 ^ USHRT_MAX,
    _mask2 ^ USHRT_MAX,
    _mask3 ^ USHRT_MAX,
    _mask4 ^ USHRT_MAX,
    _mask5 ^ USHRT_MAX,
    _mask6 ^ USHRT_MAX,
    _mask7 ^ USHRT_MAX,
    _mask8 ^ USHRT_MAX,
    _mask9 ^ USHRT_MAX
};
}

class Mask final : public MaskT<mask::C_MASK_NUM_ELEMENTS> {

public:
  Mask(uint16_t value = 1) : // value to set each bit to.
    MaskT<mask::C_MASK_NUM_ELEMENTS>(value) {
  }

  virtual ~Mask() override {
  }

public:
  bool can_adjust(uint16_t cell_value,
      uint16_t play_value) const;

  bool can_move(uint16_t play_value) const;

  bool do_adjust(uint16_t value);

  bool do_move_on_mask();

  uint16_t get_index_potential_move() const;

  uint16_t get_number_potential_moves() const;

  std::vector<uint16_t> get_potential_moves() const;

  uint16_t is_moves_exist() const;

  uint16_t is_moves_exist_adjusted(uint16_t value) const;

  inline uint16_t is_move_exists(uint16_t value) const {
    return static_cast<bool>(get_data()[value - 1]);
  }

  inline bool is_valid_play_value(uint16_t value) const {
    return (value <= Location::C_LOCATION_MOVE_MAX) &&
        value;
  }

  std::string to_string() const;

  bool do_keep_matches(uint16_t bitmask);

  bool do_remove_matches(uint16_t bitmask);

};

}
}
}

#endif
