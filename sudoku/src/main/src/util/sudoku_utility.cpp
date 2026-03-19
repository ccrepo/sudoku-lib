#include <iterator>

#include "sudoku_utility.h"

namespace cc {
namespace tools {
namespace sudoku {

std::string Utility::get_endl() {
  std::ostringstream os;

  os << std::endl;

  return os.str();
}

uint16_t Utility::is_digit(char c) {

  return c >= '0' &&
      c <= '9';
}

std::string Utility::rpad(const std::string& s,
    uint32_t size) {

  int64_t len(size - s.length());

  if (len <= 0) {
    return s;
  }

  std::string buffer(s);

  return buffer.insert(buffer.size(), len, ' ');
}

bool Utility::split(const std::string& s,
    std::vector<std::string>& buffer) {

  std::istringstream is(s);

  std::copy((std::istream_iterator<std::string> (is)),
      std::istream_iterator<std::string>(),
      std::back_inserter(buffer));

  return true;
}

uint16_t Utility::to_digit(char c) {

  static const uint16_t zero(static_cast<uint16_t>('0'));

  if (is_digit(c)) {
    return (static_cast<uint16_t>(c) - zero);
  }

  assert(!"invalid digit");
}

std::string Utility::to_lowercase(const std::string& s) {
  std::string buffer(s);

  std::transform(buffer.begin(),
      buffer.end(), buffer.begin(), ::tolower);

  return buffer;
}

std::string Utility::trim(const std::string& s) {
  return trim_l(trim_r(s));
}

std::string Utility::trim_l(const std::string& s) {
  std::string buffer(s);

  buffer.erase(buffer.begin(), std::find_if(buffer.begin(),
      buffer.end(), [](char c) {
    return !std::isspace(c);
  }));

  return buffer;
}

std::string Utility::trim_r(const std::string& s) {
  std::string buffer(s);

  buffer.erase(std::find_if(buffer.rbegin(),
      buffer.rend(), [](char c) {
    return !std::isspace(c);
  }).base(), buffer.end());

  return buffer;
}

}
}
}
