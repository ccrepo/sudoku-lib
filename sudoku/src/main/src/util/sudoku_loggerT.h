#ifndef SUDOKU_LOGGERT_H
#define SUDOKU_LOGGERT_H

#include <iostream>
#include <sstream>

#include "sudoku_clocks.h"

namespace cc {
namespace tools {
namespace sudoku {

class Fatal;
class Error;
class Warn;
class Info;
class Debug;
class Trace;
class All;
class Dev;

class Logger {
public:
  static constexpr const char *C_LOGGER_LEVEL { "SUDOKU_LOGLEVEL" };

  static constexpr const char *C_LOGGER_LEVEL_DEBUG { "debug" };
  static constexpr const char *C_LOGGER_LEVEL_DEV   { "dev" };  // NOTE: for development and testing
  static constexpr const char *C_LOGGER_LEVEL_ERROR { "error" };
  static constexpr const char *C_LOGGER_LEVEL_FATAL { "fatal" };
  static constexpr const char *C_LOGGER_LEVEL_INFO  { "info" };
  static constexpr const char *C_LOGGER_LEVEL_WARN  { "warn" };
  static constexpr const char *C_LOGGER_LEVEL_TRACE { "trace" };
  static constexpr const char *C_LOGGER_LEVEL_ALL   { "all" };
  
protected:
  Logger() {
  }
  
  virtual ~Logger() {
  }
};

template<typename T>
class LoggerT final : private Logger {

  using value_type [[maybe_unused]] = typename std::enable_if<
      std::is_same<Fatal, T>::value ||
      std::is_same<Error, T>::value ||
      std::is_same<Warn,  T>::value ||
      std::is_same<Info,  T>::value ||
      std::is_same<Debug, T>::value ||
      std::is_same<Trace, T>::value ||
      std::is_same<All,   T>::value ||
      std::is_same<Dev,   T>::value>::type;

public:
  LoggerT() :
    Logger() {
  }

  virtual ~LoggerT() override {
  }

  static inline bool is_level_on() {
    static const bool is_on(is_level_on_T());
    return is_on;
  }

public:
  void write(const std::string& s) {
    const static bool level_on(is_level_on());

    if (level_on &&
        !s.empty()) {
      std::cout << s;
      std::cout.flush();
    }
  }

  const char* get_prefix() const {
    static const char* prefix(get_prefix_T());
    return prefix;
  }

private:
  LoggerT(const LoggerT<T>&) = delete;
  LoggerT<T>& operator=(const LoggerT<T>&) = delete;

private:
  static bool is_level_on_T();

  const char* get_prefix_T() const;

};

}
}
}

#endif

