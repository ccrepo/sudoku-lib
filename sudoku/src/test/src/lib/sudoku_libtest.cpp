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

typedef std::list<std::pair<bool, const char*> (*)()> test_list;

test_list get_external();

test_list get_internal();

test_list get_ad_hoc();

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

#include "../external/sudoku_test_external_1.i"
#include "../external/sudoku_test_external_2.i"
#include "../external/sudoku_test_external_3.i"

test_list get_external() {
  return {
    external_test1,
    external_test2,
    external_test3
  };
}

test_list get_ad_hoc() {
  return {
    external_test2
  };
}

