#include "sudoku_lib_xml.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

const std::string Xml::_error_tag_close("</error>");

const std::string Xml::_index_tag_close("</i>");

const std::string Xml::_move_tag_close("</m>");

const std::string Xml::_moves_tag_close("</ms>");

const std::string Xml::_position_tag_close("</p>");

const std::string Xml::_positions_tag_close("</ps>");

const std::string Xml::_root_tag_close("</response>");

const std::string Xml::_runtime_tag_close("</runtime>");

const std::string Xml::_value_tag_close("</v>");

// -

const std::string Xml::_error_tag_open("<error>");

const std::string Xml::_index_tag_open("<i>");

const std::string Xml::_move_tag_open("<m>");

const std::string Xml::_moves_tag_open("<ms>");

const std::string Xml::_position_tag_open("<p>");

const std::string Xml::_positions_tag_open("<ps>");

const std::string Xml::_root_tag_open("<response>");

const std::string Xml::_runtime_tag_open("<runtime>");

const std::string Xml::_value_tag_open("<v>");

// -

const std::string Xml::get_moves_xml(const std::vector<std::pair<uint16_t, uint16_t>>& moves) {

  std::ostringstream os;

  os << _moves_tag_open;

  for (const auto& move : moves) {
    os << _move_tag_open
        << _index_tag_open
        << move.first
        << _index_tag_close
        << _value_tag_open
        << move.second
        << _value_tag_close
        << _move_tag_close;
  }

  os << _moves_tag_close;

  return os.str();
}

const std::string Xml::get_position_xml(const std::vector<std::pair<uint16_t, uint16_t>>& moves) {
  std::ostringstream os;

  os << _positions_tag_open;

  for (const auto& move : moves) {
    os << _position_tag_open
        << _index_tag_open
        << move.first
        << _index_tag_close
        << _value_tag_open
        << move.second
        << _value_tag_close
        << _position_tag_close;
  }

  os << _positions_tag_close;

  return os.str();
}

const std::string& Xml::get_xml_too_long_error_xml() {
  static const auto generate_xml_too_long_error_xml_lambda =
      []() -> std::string {

    std::ostringstream os;

    os << Xml::_error_tag_open
        << "generated xml too long"
        << Xml::_error_tag_close;

    return os.str();
  };

  static const std::string xml(
      generate_xml_too_long_error_xml_lambda());

  return xml;
}

const std::string& Xml::get_internal_error_xml() {
  static const auto generate_internal_error_xml_lambda =
      []() -> std::string {

    std::ostringstream os;

    os << Xml::_error_tag_open
        << "internal error xml"
        << Xml::_error_tag_close;

    return os.str();
  };

  static const std::string xml(
      generate_internal_error_xml_lambda());

  return xml;
}

const std::string Xml::get_runtime_xml(const uint32_t& runtime) {
  std::ostringstream os;

  os << Xml::_runtime_tag_open
      << runtime
      << Xml::_runtime_tag_close;

  return os.str();
}

}
}
}
}
