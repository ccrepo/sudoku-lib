#include <cstdint>
#include <iostream>

#include "sudoku_api.h"

#include "sudoku_lib_codes.h"
#include "sudoku_lib_common.h"
#include "sudoku_lib_solution.h"
#include "sudoku_lib_xml.h"
using namespace cc::tools::sudoku::lib;

int32_t get_sudoku_solution_STUB(const char* in_request,
    uint8_t* out_response,
    int32_t* out_runtime) {

  if (!Common::check_parameters(
      { out_response,
        out_runtime }
      )) {
    return Codes::bad_parameter();
  }

  std::vector<std::pair<uint16_t, uint16_t>> moves_buffer;

  try {

    memset(out_response, 0, L_CONST_RESULT_BUFFER_SIZE);
    (*out_runtime) = 0;

    Solution solution(in_request);

    uint32_t result (solution.get_sudoku_solution(moves_buffer,
        *out_runtime));

    std::ostringstream os;

    os << Xml::get_root_tag_open()
        << Xml::get_moves_xml(moves_buffer)
        << Xml::get_root_tag_close();

    if (os.tellp() >= L_CONST_RESULT_BUFFER_SIZE) {

      Common::copy_n(out_response,
          Xml::get_xml_too_long_error_xml().c_str(),
          L_CONST_RESULT_BUFFER_SIZE - 1);

      return Codes::internal_error();
    }

    Common::copy_n(out_response,
        os.str().c_str(),
        L_CONST_RESULT_BUFFER_SIZE - 1);

    return result;

  } catch (const std::exception& e) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " exception caught: "
        << e.what()
        << std::endl;

  } catch (...) {

    std::cerr << __FILE__
        << " "
        << __LINE__
        << " unknown exception caught !"
        << std::endl;

  }

  Common::copy_n(out_response,
      Xml::get_internal_error_xml().c_str(),
      L_CONST_RESULT_BUFFER_SIZE - 1);

  return Codes::internal_error();
}


