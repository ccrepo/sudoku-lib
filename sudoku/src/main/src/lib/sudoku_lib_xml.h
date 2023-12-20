#ifndef SUDOKU_LIB_XML_H
#define SUDOKU_LIB_XML_H

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

class Xml final {

public:
  static inline const std::string& get_root_tag_close() {
    return _root_tag_close;
  }

  static inline const std::string& get_root_tag_open() {
    return _root_tag_open;
  }

  static const std::string get_moves_xml(const std::vector<std::pair<uint16_t, uint16_t>>& moves);

  static const std::string get_position_xml(const std::vector<std::pair<uint16_t, uint16_t>>& moves);

  static const std::string& get_xml_too_long_error_xml();

  static const std::string& get_internal_error_xml();

  static const std::string get_runtime_xml(const uint32_t& runtime);

private:
  static const std::string _error_tag_close;

  static const std::string _index_tag_close;

  static const std::string _move_tag_close;

  static const std::string _moves_tag_close;

  static const std::string _position_tag_close;

  static const std::string _positions_tag_close;

  static const std::string _root_tag_close;

  static const std::string _runtime_tag_close;

  static const std::string _value_tag_close;

  //

  static const std::string _error_tag_open;

  static const std::string _index_tag_open;

  static const std::string _move_tag_open;

  static const std::string _moves_tag_open;

  static const std::string _position_tag_open;

  static const std::string _positions_tag_open;

  static const std::string _root_tag_open;

  static const std::string _runtime_tag_open;

  static const std::string _value_tag_open;

private:
  Xml() = delete;

};

}
}
}
}

#endif
