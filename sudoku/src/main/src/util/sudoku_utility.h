#ifndef SUDOKU_UTILITY_H
#define SUDOKU_UTILITY_H

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <tuple>

#include "sudoku_types.h"

namespace cc {
namespace tools {
namespace sudoku {

class Utility final {

public:
  static std::string get_endl();

  static uint16_t is_digit(char c);

  static std::string rpad(const std::string& s,
      uint32_t size);

  static bool split(const std::string& s, std::vector<std::string>& buffer);

  static uint16_t to_digit(char c);

  static std::string to_lowercase(const std::string& s);

  static std::string trim(const std::string& s);

  static std::string trim_l(const std::string& s);

  static std::string trim_r(const std::string& s);

  template<typename T>
  static void concat(std::ostringstream& os, T t);

  template<typename T, typename ... Args>
  static std::string concat(std::ostringstream& os, T t, Args ... args);

private:
  Utility() = delete;

};

//-

template<typename T>
void Utility::concat(std::ostringstream& os, T t) {
  os << t;
}

template<typename T, typename ... Args>
std::string Utility::concat(std::ostringstream& os, T t, Args ... args) {
  os << t;

  concat(os, args...);

  return os.str();
}

}
}
}

#endif
