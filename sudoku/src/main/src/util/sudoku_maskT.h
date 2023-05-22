#ifndef SUDOKU_MASKT_H
#define SUDOKU_MASKT_H

#include <array>

namespace cc {
namespace tools {
namespace sudoku {

template<std::size_t N>
class MaskT {

private:
  template <std::size_t ... S>
  constexpr std::array<unsigned char, sizeof...(S)>
  create(unsigned char value, std::index_sequence<S...>) {
    return { { ( static_cast<void>(S) , value)... } };
  }

public:
  MaskT(bool value = 1) :
    _data(create(static_cast<unsigned char>(value), std::make_index_sequence<N>())) {
    static_assert(N > 0 && N <= 64, "limit breach");
  }

  MaskT(const MaskT<N>& mask) :
    _data(mask._data) {
  }

  virtual ~MaskT() {
  }

  inline MaskT<N>& operator=(const MaskT<N> mask) {
    _data = mask._data;

    return (*this);
  }

  unsigned char& operator[](std::size_t i);

  inline const std::array<unsigned char, N>& get_data() const {
    return _data;
  }

  inline void set_data(uint16_t index, unsigned char value) {
    _data[index] = value;
  }

  inline size_t size() const {
    return N;
  }

  const std::string to_string() const;

private:
  std::array<unsigned char, N> _data;

};

//-

template<std::size_t N>
const std::string MaskT<N>::to_string() const {

  std::ostringstream os;

  for (std::size_t i(0); i < N; ++i) {
    if (_data[i]) {
      os << (i+1);
    } else {
      os << '.';
    }
  }

  return os.str();
}

template<std::size_t N>
unsigned char& MaskT<N>::operator[](std::size_t i) {
  if (i >= N) {
    throw std::out_of_range("index too large");
  }

  return _data[i];
}

}
}
}

#endif
