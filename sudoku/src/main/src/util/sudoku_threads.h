#ifndef SUDOKU_THREADS_H
#define SUDOKU_THREADS_H

#include <iomanip>
#include <sstream>
#include <thread>

#include "sudoku_durations.h"
#include "sudoku_maths.h"
#include "sudoku_atomic_counter.h"

namespace cc {
namespace tools {
namespace sudoku {

class Threads final {

public:
  static const std::string& get_thread_name() {
    thread_local static const std::string thread_name(
        get_thread_descriptor(get_thread_id()));

    return thread_name;
  }

public:
  static void do_sleep(uint32_t ms);

public:
  static inline void do_minimum_to_miniscule_rand_sleep() {
    thread_local static const auto ms(Maths::rand_in_range
        (Durations::C_DURATIONS_MINIMUM, Durations::C_DURATIONS_MINISCULE));

    do_sleep(ms);
  }

  static inline void do_miniscule_to_shortest_rand_sleep() {
    thread_local static const auto ms(Maths::rand_in_range
        (Durations::C_DURATIONS_MINISCULE, Durations::C_DURATIONS_SHORTEST));

    do_sleep(ms);
  }

  static inline void do_short_to_medium_rand_sleep() {
    thread_local static const auto ms(Maths::rand_in_range
        (Durations::C_DURATIONS_SHORT, Durations::C_DURATIONS_MEDIUM));

    do_sleep(ms);
  }

  static inline void do_shorter_to_short_rand_sleep() {
    thread_local static const auto ms(Maths::rand_in_range
        (Durations::C_DURATIONS_SHORTER, Durations::C_DURATIONS_SHORT));

    do_sleep(ms);
  }

  static inline void do_short_sleep() {
    do_sleep(Durations::C_DURATIONS_SHORT);
  }

  static inline void do_shorter_sleep() {
    do_sleep(Durations::C_DURATIONS_SHORTER);
  }

  static inline void do_miniscule_sleep() {
    do_sleep(Durations::C_DURATIONS_MINISCULE);
  }

private:
  static uint64_t get_thread_id() {
    thread_local static const uint64_t id(
        _thread_id_counter.increment());

    return id;
  }

  static std::string get_thread_descriptor(uint64_t id) {
    std::ostringstream os;

    os << _thread_desc_prefix
        << std::setfill('0')
        << std::setw(3)
        << id;

    return os.str();
  }

private:
  static const std::string _thread_desc_prefix;

  static AtomicCounterU64Relaxed _thread_id_counter;

private:
  Threads() = delete;

};

}
}
}

#endif
