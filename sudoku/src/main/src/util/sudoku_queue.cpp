#include "sudoku_queue.h"

#include "sudoku_globals.h"
#include "sudoku_log.h"
#include "sudoku_maths.h"
#include "sudoku_workI.h"
#include "sudoku_workerpool.h"

namespace cc {
namespace tools {
namespace sudoku {

bool Queue::push(const std::shared_ptr<WorkI>& element, bool retry) {

  thread_local static const auto ms(Maths::get_short_rand_in_range());

  if (is_exit()) {
    return false;
  }

  std::unique_lock<std::timed_mutex> lock(_write_lock_mutex, std::defer_lock);

  uint32_t write_lock_retries(C_QUEUE_WRITE_LOCK_RETRIES);

  while (write_lock_retries-- &&
      !is_exit()) {

    if (lock.try_lock_for(std::chrono::milliseconds(ms))) {

      _elements.push_back(element);

      _queue_size_value.set(_elements.size());

      return true;
    }

    if (!retry) {
      break;
    }
  }

  return false;
}

bool Queue::push(const std::vector<std::shared_ptr<WorkI>>& elements, bool retry) {

  thread_local static const auto ms(Maths::get_short_rand_in_range());

  if (is_exit()) {
    return false;
  }

  std::unique_lock<std::timed_mutex> lock(_write_lock_mutex, std::defer_lock);

  uint32_t write_lock_retries(C_QUEUE_WRITE_LOCK_RETRIES);

  while (write_lock_retries-- &&
      !is_exit()) {

    if (lock.try_lock_for(std::chrono::milliseconds(ms))) {

      std::move(elements.begin(), elements.end(),
          std::back_inserter(_elements));

      _queue_size_value.set(_elements.size());

      return true;
    }

    if (!retry) {
      break;
    }
  }

  return false;
}

bool Queue::pop(std::shared_ptr<WorkI>& element, bool retry) {

  thread_local static const auto ms(Maths::get_short_rand_in_range());

  if (is_exit()) {
    return false;
  }

  std::unique_lock<std::timed_mutex> lock(_write_lock_mutex, std::defer_lock);

  uint32_t write_lock_retries(C_QUEUE_WRITE_LOCK_RETRIES);

  while (write_lock_retries-- &&
      !is_exit()) {

    if (lock.try_lock_for(std::chrono::milliseconds(ms))) {

      if (_elements.empty()) {

        _queue_size_value.set(0);

        return false;
      }

      element = _elements.front();

      _elements.pop_front();

      _queue_size_value.set(_elements.size());

      return true;
    }

    if (!retry) {
      break;
    }
  }

  return false;
}

bool Queue::pop(std::vector<std::shared_ptr<WorkI>>& elements,
    uint32_t pop_count, bool retry) {

  thread_local static const auto ms(Maths::get_short_rand_in_range());

  if (is_exit() ||
      !pop_count) {
    return false;
  }

  std::unique_lock<std::timed_mutex> lock(_write_lock_mutex, std::defer_lock);

  uint32_t write_lock_retries(C_QUEUE_WRITE_LOCK_RETRIES);

  while (write_lock_retries-- &&
      !is_exit()) {

    if (lock.try_lock_for(std::chrono::milliseconds(ms))) {

      if (_elements.empty()) {

        _queue_size_value.set(0);

        return false;
      }

      uint32_t limit(Maths::min(pop_count, _elements.size()));

      while (limit--) {

        if (is_exit()) {
          _queue_size_value.set(_elements.size());

          return false;
        }

        elements.push_back(_elements.front());

        _elements.pop_front();
      }

      _queue_size_value.set(_elements.size());

      return true;
    }

    if (!retry) {
      break;
    }
  }

  return false;
}

bool Queue::pop(std::vector<std::pair<std::shared_ptr<WorkI>, std::shared_ptr<Autocall>>>& elements,
    uint32_t pop_count, bool retry) {

  thread_local static const auto ms(Maths::get_short_rand_in_range());

  if (is_exit() ||
      !pop_count) {
    return false;
  }

  std::unique_lock<std::timed_mutex> lock(_write_lock_mutex, std::defer_lock);

  uint32_t write_lock_retries(C_QUEUE_WRITE_LOCK_RETRIES);

  while (write_lock_retries-- &&
      !is_exit()) {

    if (lock.try_lock_for(std::chrono::milliseconds(ms))) {

      if (_elements.empty()) {

        _queue_size_value.set(0);

        return false;
      }

      uint32_t limit(Maths::min(pop_count, _elements.size()));

      while (limit--) {

        if (is_exit()) {

          _queue_size_value.set(_elements.size());

          return false;
        }

        elements.push_back( { _elements.front(),
          std::shared_ptr<Autocall>(new Autocall(_elements.front())) } );

        _elements.pop_front();
      }

      _queue_size_value.set(_elements.size());

      return true;
    }

    if (!retry) {
      break;
    }
  }

  return false;
}

bool Queue::do_condition_wait() {

  if (is_exit()) {

    do_condition_wake();

    return true;
  }

  try {

    std::shared_lock<std::shared_mutex> lock(_condition_mutex);

    LOGTRACE("waiting");

    auto status = _condition_variable.wait_for(lock, std::chrono::milliseconds(
        C_QUEUE_CONDITION_VARIABLE_WAIT_TIMEOUT));

    if (status == std::cv_status::timeout) {
      LOGTRACE("wait timeout");

      return true;
    }

    LOGTRACE("wait no timeout (woken)");

    return true;

  } catch (const std::exception& e) {
    
    std::cerr << __FILE__
        << " "
        << __LINE__
        << " exception caught: "
        << e.what()
        << std::endl;
    
  } catch (...) {
    
    std::cerr << __FILE__
        << " "
        << __LINE__
        << " unknown exception caught !"
        << std::endl;
    
  }

  return false;
}

bool Queue::do_condition_wake() {

  try {
    std::shared_lock<std::shared_mutex> lock(_condition_mutex);

    LOGTRACE("waking");

    _condition_variable.notify_all();

  } catch (const std::exception& e) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " exception caught: "
        << e.what()
        << std::endl;

  } catch (...) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " unknown exception caught !"
        << std::endl;

  }

  return true;
}

bool Queue::do_exit_queue() {
  _exit_queue_flag.set();

  return true;
}

Queue::Queue() :
  _elements(),
  _queue_size_value(0),
  _write_lock_mutex(),
  _condition_mutex(),
  _condition_variable(),
  _exit_queue_flag() {
}

Queue::~Queue() {

  try {

    LOGTRACE("destroying ", reinterpret_cast<void*>(this));

    std::unique_lock<std::timed_mutex> lock(_write_lock_mutex, std::defer_lock);

    thread_local static const auto ms(Maths::get_short_rand_in_range());

    while (!lock.try_lock_for(std::chrono::milliseconds(ms))) {
      LOGTRACE("waiting for lock");
    }

    _elements.clear();

  } catch (const std::exception& e) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " exception caught: "
        << e.what()
        << std::endl;

  } catch (...) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " unknown exception caught !"
        << std::endl;

  }
}

bool Queue::is_exit() const {

  if (_exit_queue_flag.test()) {
    return true;
  }

  if (Globals::is_exit_all_global()) {
    return true;
  }

  return false;
}


}
}
}
