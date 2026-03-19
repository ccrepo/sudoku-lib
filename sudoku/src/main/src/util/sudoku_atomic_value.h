#ifndef SUDOKU_ATOMIC_VALUE_H
#define SUDOKU_ATOMIC_VALUE_H

#include <atomic>

namespace cc {
namespace tools {
namespace sudoku {


template<typename T>
class AtomicValueT {

  using value_type [[maybe_unused]] =
      typename std::enable_if<

  (std::is_same<int64_t,  T>::value) ||

  (std::is_same<int32_t,  T>::value) ||

  (std::is_same<int16_t,  T>::value) ||

  (std::is_same<int8_t,   T>::value) ||

  (std::is_same<uint64_t, T>::value) ||

  (std::is_same<uint32_t, T>::value) ||

  (std::is_same<uint16_t, T>::value) ||

  (std::is_same<uint8_t,  T>::value)>::type;

public:
  AtomicValueT(T value = 0) :
    _value(value) {
  }

  virtual ~AtomicValueT() {
  }

public:
  inline T get() const {
    return _value.load(std::memory_order_relaxed);
  }

  inline void set(const T& value) {
    _value.store(value, std::memory_order_relaxed);
  }

private:
  std::atomic<T> _value;

private:
  AtomicValueT(const AtomicValueT&) = delete;
  AtomicValueT& operator=(const AtomicValueT&) = delete;

};

typedef AtomicValueT<int64_t>  AtomicValue64Relaxed;
typedef AtomicValueT<int32_t>  AtomicValue32Relaxed;
typedef AtomicValueT<int16_t>  AtomicValue16Relaxed;
typedef AtomicValueT<int8_t>   AtomicValue8Relaxed;

typedef AtomicValueT<uint64_t> AtomicValueU64Relaxed;
typedef AtomicValueT<uint32_t> AtomicValueU32Relaxed;
typedef AtomicValueT<uint16_t> AtomicValueU16Relaxed;
typedef AtomicValueT<uint8_t>  AtomicValueU8Relaxed;

}
}
}

#endif

