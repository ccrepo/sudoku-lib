#ifndef SUDOKU_AUTOCALLI_H
#define SUDOKU_AUTOCALLI_H

#include <functional>

namespace cc {
namespace tools {
namespace sudoku {

class AutocallI {

public:
  AutocallI() {
  }

  virtual ~AutocallI() {
  }

public:
  virtual std::function<void ()> get_autocall_callback_lambda() = 0;

private:
  AutocallI(const AutocallI&) = delete;
  AutocallI& operator=(const AutocallI&) = delete;

};

}
}
}

#endif
