#ifndef SUDOKU_TEST_POSITION_H
#define SUDOKU_TEST_POSITION_H

#include <string>
#include <vector>

namespace cc {
namespace tools {
namespace sudoku {
namespace test {

class TestPosition final {

public:


public:
  static const std::string& get_any_position();

  static const std::string _position1;
  static const std::string _position2;
  static const std::string _position3;
  static const std::string _position4;
  static const std::string _position5;

  static const std::vector<std::reference_wrapper<const std::string>> _positions;

private:
  TestPosition() = delete;

};

}
}
}
}

#endif
