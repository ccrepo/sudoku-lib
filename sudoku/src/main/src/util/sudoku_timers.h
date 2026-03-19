#ifndef SUDOKU_TIMERS_H
#define SUDOKU_TIMERS_H

#include <cstdint>
#include <memory>

#include "sudoku_clocks.h"

namespace cc {
namespace tools {
namespace sudoku {

class Timer1 final {

public:
  explicit Timer1(const std::shared_ptr<uint32_t>& result) : _result(result),
    _start(Clocks::steady_clock_now_MS()) {
  }

  ~Timer1() {
    if (std::shared_ptr<uint32_t> result = _result.lock()) {
      (*result) = Clocks::steady_clock_now_MS() - this->_start;
    }
  }

private:
  std::weak_ptr<uint32_t> _result;
  const uint32_t _start;

private:
  Timer1(const Timer1&) = delete;
  Timer1& operator=(const Timer1&) = delete;

};

class Timer2 final {

public:
  explicit Timer2(int32_t& result) : _result(result),
    _start(Clocks::steady_clock_now_MS()) {
  }

  ~Timer2() {
    _result = Clocks::steady_clock_now_MS() - this->_start;
  }

private:
  int32_t& _result;
  const int32_t _start;

private:
  Timer2(const Timer2&) = delete;
  Timer2& operator=(const Timer2&) = delete;

};

}
}
}

#endif
