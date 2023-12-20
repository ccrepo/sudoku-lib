#ifndef SUDOKU_THREAD_H
#define SUDOKU_THREAD_H

#include <iomanip>
#include <sstream>
#include <thread>
#include <functional>

namespace cc {
namespace tools {
namespace sudoku {

class Thread {

public:
  Thread() : _thread() {
  }

  virtual ~Thread();

protected:
  void start(std::function<void ()>& func) {
    _thread.reset(new std::thread(func));
  }

private:
  std::unique_ptr<std::thread> _thread;

private:
  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

};

}
}
}

#endif
