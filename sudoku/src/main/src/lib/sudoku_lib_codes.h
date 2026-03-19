#ifndef SUDOKU_LIB_CODES_H
#define SUDOKU_LIB_CODES_H

#include <array>
#include <cstdint>
#include <utility>

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

class Codes final {

private:
  static constexpr const std::pair<uint16_t, const char*> code_0_success        {0, "Success."};
  static constexpr const std::pair<uint16_t, const char*> code_1_bad_parameter  {1, "Bad Parameter."};
  static constexpr const std::pair<uint16_t, const char*> code_2_setup_failed   {2, "Setup Failed."};
  static constexpr const std::pair<uint16_t, const char*> code_3_solved_early   {3, "Solved Early."};
  static constexpr const std::pair<uint16_t, const char*> code_4_no_solution    {4, "No Solution."};
  static constexpr const std::pair<uint16_t, const char*> code_5_timeout        {5, "Timeout."};
  static constexpr const std::pair<uint16_t, const char*> code_6_internal_error {6, "Internal Error."};
  static constexpr const std::pair<uint16_t, const char*> code_7_shutdown_exit  {7, "Shutdown Exit."};
  static constexpr const std::pair<uint16_t, const char*> code_8_server_busy    {8, "Server Busy."};

public:
  static constexpr const std::array<std::pair<uint16_t, const char*>, 9> _codes {
    code_0_success,
    code_1_bad_parameter,
    code_2_setup_failed,
    code_3_solved_early,
    code_4_no_solution,
    code_5_timeout,
    code_6_internal_error,
    code_7_shutdown_exit,
    code_8_server_busy
  };

public:
  static inline uint16_t success() {
    return code_0_success.first;
  }

  static inline uint16_t bad_parameter() {
    return code_1_bad_parameter.first;
  }

  static inline uint16_t setup_failed() {
    return code_2_setup_failed.first;
  }

  static inline uint16_t solved_early() {
    return code_3_solved_early.first;
  }

  static inline uint16_t no_solution() {
    return code_4_no_solution.first;
  }

  static inline uint16_t timeout() {
    return code_5_timeout.first;
  }

  static inline uint16_t internal_error() {
    return code_6_internal_error.first;
  }

  static inline uint16_t shutdown_exit() {
    return code_7_shutdown_exit.first;
  }

  static inline uint16_t server_busy() {
    return code_8_server_busy.first;
  }

private:
  Codes() = delete;
};

}
}
}
}

#endif
