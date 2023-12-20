#ifndef SUDOKU_WORKI_H
#define SUDOKU_WORKI_H

#include <vector>
#include <cstdint>
#include <memory>
#include <functional>

#include "sudoku_autocallI.h"

namespace cc {
namespace tools {
namespace sudoku {

class WorkI : public AutocallI {

public:
  WorkI() : AutocallI() {
  }

  virtual ~WorkI() override;

public:
  virtual bool do_solve() = 0;

  virtual bool do_lock() = 0;

public:
  virtual bool is_interrupted() const = 0;

  virtual bool is_locked() const = 0;

  virtual bool is_processed() const = 0;

  virtual bool is_solved() const = 0;

  virtual bool is_timeout() const = 0;

public:
  static uint64_t get_processed_count(
      const std::vector<std::shared_ptr<WorkI>>& work);

  static uint64_t get_solved_count(
      const std::vector<std::shared_ptr<WorkI>>& work);

  static uint64_t get_interrupted_count(
      const std::vector<std::shared_ptr<WorkI>>& work);

public:
  virtual void set_is_processed() = 0;

  virtual void set_is_interrupted() = 0;
};

}
}
}

#endif
