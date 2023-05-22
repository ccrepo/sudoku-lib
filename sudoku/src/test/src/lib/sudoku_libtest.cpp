#include <chrono>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <tuple>
#include <cstring>

#include <chrono>
using U_CLOCK = std::chrono::steady_clock;

#include "sudoku_api.h"

#include "sudoku_test_position.h"

#define SUDOKU_FULLTEST

#ifdef SUDOKU_FULLTEST
#include "sudoku_geometry.h"
#include "sudoku_log.h"
#include "sudoku_mask.h"
#include "sudoku_board.h"
#include "sudoku_maths.h"
#endif

typedef std::list<std::pair<bool, const char*> (*)()> test_list;

test_list get_external();

test_list get_internal();

test_list get_ad_hoc();

// TODO
// TODO 1. move thread and concurrency parameters to configuration.
// TODO 2. reduce checks in check solved as work duplicated.
// TODO 3. add load balancing

int main() {
  std::cout << "start." << std::endl << std::flush;

  for (auto& tests : { get_ad_hoc() }) {

    for (auto& test : tests) {

      auto start_time(U_CLOCK::now());

      auto r(test());

      if (r.first) {

        std::cout << "test "
            << r.second
            << " ok"
            << std::endl;
      } else {

        std::cout << "test "
            << r.second
            << " NOT ok"
            << std::endl;
      }

      auto end_time(U_CLOCK::now());

      std::cout << "total test "
          << r.second
          << " runtime: "
          << (duration_cast<std::chrono::milliseconds> (end_time - start_time).count())
          << " ms."
          << std::endl
          << "stop."
          << std::endl
          << std::flush;
    }

  }

  std::cout.flush();

  return 0;
}

#ifdef SUDOKU_FULLTEST
#include "../internal/sudoku_test_internal_1.incl.h"
#include "../internal/sudoku_test_internal_2.incl.h"
#endif

#include "../external/sudoku_test_external_1.incl.h"
#include "../external/sudoku_test_external_2.incl.h"

test_list get_external() {
  return {
    external_test1, external_test2
  };
}

test_list get_internal() {
  return {
#ifdef SUDOKU_FULLTEST
    internal_test1, internal_test2
#endif
  };
}

test_list get_ad_hoc() {
  return {
    external_test1
  };
}

