#ifndef SUDOKU_ATOMIC_FLAG_H
#define SUDOKU_ATOMIC_FLAG_H

#include <atomic>

namespace cc {
namespace tools {
namespace sudoku {

class AtomicFlagSeqCst final {

public:
  AtomicFlagSeqCst() :
    _flag(false) {
  }

public:
  inline bool test() const {
    return _flag.test(std::memory_order_seq_cst);
  }

  inline void set() {
    _flag.test_and_set(std::memory_order_seq_cst);
  }

  inline bool test_and_set() {
    return _flag.test_and_set(std::memory_order_seq_cst);
  }

private:
  std::atomic_flag _flag;

private:
  AtomicFlagSeqCst(const AtomicFlagSeqCst&) = delete;
  AtomicFlagSeqCst& operator=(const AtomicFlagSeqCst&) = delete;

};

class AtomicFlagRelAcq final {

public:
  AtomicFlagRelAcq() :
    _flag(false) {
  }

public:
  inline bool test() const {
    return _flag.test(std::memory_order_acquire);
  }

  inline void set() {
    _flag.test_and_set(std::memory_order_release);
  }

  inline bool test_and_set() {
    return _flag.test_and_set(std::memory_order_acq_rel);
  }

private:
  std::atomic_flag _flag;

private:
  AtomicFlagRelAcq(const AtomicFlagRelAcq&) = delete;
  AtomicFlagRelAcq& operator=(const AtomicFlagRelAcq&) = delete;

};

class AtomicFlagSemiRelaxed final {

public:
  AtomicFlagSemiRelaxed() :
    _flag(false),
    _sync_control(false) {
  }

public:
  inline bool test() const {
    return _flag.test(std::memory_order_relaxed) &&
        _sync_control.test(std::memory_order_acquire);
  }

  inline void set() {
    _flag.test_and_set(std::memory_order_relaxed);
    _sync_control.test_and_set(std::memory_order_acq_rel);
  }

  inline bool test_and_set() {
    thread_local static bool prev(false);
    prev = _flag.test_and_set(std::memory_order_relaxed);
    _sync_control.test_and_set(std::memory_order_acq_rel);
    return prev;
  }

private:
  std::atomic_flag _flag;
  std::atomic_flag _sync_control;

private:
  AtomicFlagSemiRelaxed(const AtomicFlagSemiRelaxed&) = delete;
  AtomicFlagSemiRelaxed& operator=(const AtomicFlagSemiRelaxed&) = delete;

};

}
}
}

#endif
