#include <cstdlib>
#include <functional>
#include <sstream>
#include <chrono>
using U_CLOCK = std::chrono::steady_clock;

#include "sudoku_test_position.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace test {

const std::string TestPosition::_position1("3 0 0 2 0 0 0 0 0 0 0 0 1 0 7 "
    " 0 0 0 7 0 6 0 3 0 5 0 0 0 7 0 0 0 9 0 8 0 9 0 0 0 "
    " 2 0 0 0 4 0 1 0 8 0 0 0 5 0 0 0 9 0 4 0 3 0 1 0 0 "
    " 0 7 0 2 0 0 0 0 0 0 0 0 8 0 0 6");

const std::string TestPosition::_position2("3 5 1 2 8 6 4 9 7 4 9 2 1 5 7 6 3 8 "
    "7 8 6 9 3 4 5 1 0 2 7 5 4 6 9 1 8 3 9 3 8 5 2 1 7 6 4 "
    "6 1 4 8 7 3 2 5 9 8 2 9 6 4 5 3 7 1 1 6 3 7 9 2 8 4 5 "
    "5 4 7 3 1 8 9 2 6");

const std::string TestPosition::_position3("3 0 1 2 0 0 0 0 7 0 0 0 1 0 7 0 0 0 "
    " 7 0 6 9 3 4 5 1 0 0 7 0 4 0 9 0 8 0 9 0 0 0 2 0 0 7 4 "
    " 0 1 0 8 7 0 0 5 0 0 0 9 0 4 0 3 2 1 0 0 0 7 0 2 8 0 5 "
    " 0 0 0 3 0 8 7 0 6 ");

const std::string TestPosition::_position4("7 0 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
    " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
    " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
    " 0 0 0 0 0 0 0 0 0 ");

const std::string TestPosition::_position5("3 5 1 2 8 6 4 9 7 4 9 2 1 5 7 6 3 8 "
    "7 8 6 9 3 4 5 1 2 2 7 5 4 6 9 1 8 3 9 3 8 5 2 1 7 6 4 "
    "6 1 4 8 7 3 2 5 9 8 2 9 6 4 5 3 7 1 1 6 3 7 9 2 8 4 5 "
    "5 4 7 3 1 8 9 2 6");

namespace _ {
  const std::vector<std::reference_wrapper<const std::string>> generate_positions() {
    std::vector<std::reference_wrapper<const std::string>> positions;

    positions.push_back(std::reference_wrapper(TestPosition::_position1));
    positions.push_back(std::reference_wrapper(TestPosition::_position2));
    positions.push_back(std::reference_wrapper(TestPosition::_position3));
    positions.push_back(std::reference_wrapper(TestPosition::_position4));
    positions.push_back(std::reference_wrapper(TestPosition::_position5));

    return positions;
  }
}

const std::vector<std::reference_wrapper<const std::string>> TestPosition::_positions(_::generate_positions());

const std::string& TestPosition::get_any_position() {
  srand((std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::system_clock::now().time_since_epoch()).count())%100);

  return _positions[rand()%_positions.size()];
}

}
}
}
}
