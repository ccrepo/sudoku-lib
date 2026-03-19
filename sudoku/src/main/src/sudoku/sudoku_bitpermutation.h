#ifndef SUDOKU_BITPERMUTATION_H
#define SUDOKU_BITPERMUTATION_H

#include <thread>
#include <array>
#include <vector>

namespace cc {
namespace tools {
namespace sudoku {

class BitPermutation final {

public:
  static const std::vector<uint16_t>& get_bitpermutation_n(uint16_t n);

public:
  BitPermutation() {
  }

  ~BitPermutation() {
  }

public:
  static inline const uint16_t C_BITPERMUTATION_FULL_PERMUTATION_ON { 511 + 1 };

private:
  static std::vector<uint16_t> create_bitpermutation_n(uint16_t n);

private:
  static const std::vector<uint16_t> _bitpermutation_n_0;
  static const std::vector<uint16_t> _bitpermutation_n_1;
  static const std::vector<uint16_t> _bitpermutation_n_2;
  static const std::vector<uint16_t> _bitpermutation_n_3;
  static const std::vector<uint16_t> _bitpermutation_n_4;
  static const std::vector<uint16_t> _bitpermutation_n_5;
  static const std::vector<uint16_t> _bitpermutation_n_6;
  static const std::vector<uint16_t> _bitpermutation_n_7;
  static const std::vector<uint16_t> _bitpermutation_n_8;
  static const std::vector<uint16_t> _bitpermutation_n_9;

};

}
}
}

#endif
