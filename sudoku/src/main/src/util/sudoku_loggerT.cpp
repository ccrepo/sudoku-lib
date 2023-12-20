#include "sudoku_config.h"
#include "sudoku_loggerT.h"

namespace cc {
namespace tools {
namespace sudoku {

template<>
const char* LoggerT<Debug>::get_prefix_T() const {
  return C_LOGGER_LEVEL_DEBUG;
}

template<>
const char* LoggerT<Dev>::get_prefix_T() const {
  return C_LOGGER_LEVEL_DEV;
}

template<>
const char* LoggerT<Error>::get_prefix_T() const {
  return C_LOGGER_LEVEL_ERROR;
}

template<>
const char* LoggerT<Fatal>::get_prefix_T() const {
  return C_LOGGER_LEVEL_FATAL;
}

template<>
const char* LoggerT<Info>::get_prefix_T() const {
  return C_LOGGER_LEVEL_INFO;
}

template<>
const char* LoggerT<Trace>::get_prefix_T() const {
  return C_LOGGER_LEVEL_TRACE;
}

template<>
const char* LoggerT<All>::get_prefix_T() const {
  return C_LOGGER_LEVEL_ALL;
}

template<>
const char* LoggerT<Warn>::get_prefix_T() const {
  return C_LOGGER_LEVEL_WARN;
}

template<>
bool LoggerT<Dev>::is_level_on_T() {
  return true;
}

template<>
bool LoggerT<All>::is_level_on_T() {
  static const bool is_level(
      Config::get_config()->is_log_all());

  return is_level;
}

template<>
bool LoggerT<Trace>::is_level_on_T() {

  static const bool is_level(
      Config::get_config()->is_log_trace()
      || LoggerT<All>::is_level_on());

  return is_level;
}

template<>
bool LoggerT<Debug>::is_level_on_T() {

  static const bool is_level(
      Config::get_config()->is_log_debug()
      || LoggerT<Trace>::is_level_on());

  return is_level;
}

template<>
bool LoggerT<Info>::is_level_on_T() {

  static const bool is_level(
      Config::get_config()->is_no_level() ?
          true :
          (Config::get_config()->is_log_info()
              || LoggerT<Debug>::is_level_on()));

  return is_level;
}

template<>
bool LoggerT<Warn>::is_level_on_T() {

  static const bool is_level(
      Config::get_config()->is_no_level() ?
          true :
          (Config::get_config()->is_log_warn()
              || LoggerT<Info>::is_level_on()));

  return is_level;
}

template<>
bool LoggerT<Error>::is_level_on_T() {

  static const bool is_level(
      Config::get_config()->is_no_level() ?
          true :
          (Config::get_config()->is_log_error()
              || LoggerT<Warn>::is_level_on()));

  return is_level;
}

template<>
bool LoggerT<Fatal>::is_level_on_T() {

  static const bool is_level(
      Config::get_config()->is_no_level() ?
          true :
          (Config::get_config()->is_log_fatal()
              || LoggerT<Error>::is_level_on()));

  return is_level;
}


}
}
}
