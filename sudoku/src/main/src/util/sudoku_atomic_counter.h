#ifndef SUDOKU_ATOMIC_COUNTER_H
#define SUDOKU_ATOMIC_COUNTER_H

#include <atomic>

namespace cc {
namespace tools {
namespace sudoku {


template<typename T>
class AtomicCounterT {

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
  AtomicCounterT(T counter = 1) :
    _counter(counter) {
  }

  virtual ~AtomicCounterT() {
  }

public:
  inline T increment() {
    return _counter.fetch_add(1, std::memory_order_relaxed);
  }

private:
  std::atomic<T> _counter;

private:
  AtomicCounterT(const AtomicCounterT&) = delete;
  AtomicCounterT& operator=(const AtomicCounterT&) = delete;

};

typedef AtomicCounterT<int64_t>  AtomicCounter64Relaxed;
typedef AtomicCounterT<int32_t>  AtomicCounter32Relaxed;
typedef AtomicCounterT<int16_t>  AtomicCounter16Relaxed;
typedef AtomicCounterT<int8_t>   AtomicCounter8Relaxed;

typedef AtomicCounterT<uint64_t> AtomicCounterU64Relaxed;
typedef AtomicCounterT<uint32_t> AtomicCounterU32Relaxed;
typedef AtomicCounterT<uint16_t> AtomicCounterU16Relaxed;
typedef AtomicCounterT<uint8_t>  AtomicCounterU8Relaxed;

}
}
}

#endif

