#include "sudoku_bitpermutation.h"
#include "sudoku_mask.h"

namespace cc {
namespace tools {
namespace sudoku {

namespace bitpermutation {

static std::array<uint16_t, BitPermutation::C_BITPERMUTATION_FULL_PERMUTATION_ON> bit_counts;

static bool create_bitpermutations() {

  for (uint16_t i(1); i <= BitPermutation::C_BITPERMUTATION_FULL_PERMUTATION_ON; ++i) {

    bit_counts[i] =
        ((i & bits::_masks[0]) ? 1 : 0) +
        ((i & bits::_masks[1]) ? 1 : 0) +
        ((i & bits::_masks[2]) ? 1 : 0) +
        ((i & bits::_masks[3]) ? 1 : 0) +
        ((i & bits::_masks[4]) ? 1 : 0) +
        ((i & bits::_masks[5]) ? 1 : 0) +
        ((i & bits::_masks[6]) ? 1 : 0) +
        ((i & bits::_masks[7]) ? 1 : 0) +
        ((i & bits::_masks[8]) ? 1 : 0);
  }

  return true;
}

static bool created_bitpermutationss(create_bitpermutations());

}

std::vector<uint16_t> BitPermutation::create_bitpermutation_n(uint16_t n) {

  std::vector<uint16_t> buffer;

  for (uint16_t i(1); i <= C_BITPERMUTATION_FULL_PERMUTATION_ON; ++i) {
    if (bitpermutation::bit_counts[i] == n) {
      buffer.push_back(i);
    }
  }

  return buffer;
}

const std::vector<uint16_t> BitPermutation::_bitpermutation_n_0 {} ;
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_1(create_bitpermutation_n(1));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_2(create_bitpermutation_n(2));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_3(create_bitpermutation_n(3));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_4(create_bitpermutation_n(4));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_5(create_bitpermutation_n(5));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_6(create_bitpermutation_n(6));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_7(create_bitpermutation_n(7));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_8(create_bitpermutation_n(8));
const std::vector<uint16_t> BitPermutation::_bitpermutation_n_9(create_bitpermutation_n(9));

const std::vector<uint16_t>& BitPermutation::get_bitpermutation_n(uint16_t n) {

  switch (n) {

  case 1:
    return _bitpermutation_n_1;
  case 2:
    return _bitpermutation_n_2;
  case 3:
    return _bitpermutation_n_3;
  case 4:
    return _bitpermutation_n_4;
  case 5:
    return _bitpermutation_n_5;
  case 6:
    return _bitpermutation_n_6;
  case 7:
    return _bitpermutation_n_7;
  case 8:
    return _bitpermutation_n_8;
  case 9:
    return _bitpermutation_n_9;
  default:
    return _bitpermutation_n_0;
  }
}

}
}
}
