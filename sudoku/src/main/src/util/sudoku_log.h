#ifndef SUDOKU_LOG_H
#define SUDOKU_LOG_H

#include <iostream>
#include <sstream>
#include <memory>

#include "sudoku_loggerT.h"
#include "sudoku_system.h"
#include "sudoku_utility.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace logger {

extern thread_local const std::string thread_name;

inline std::ostringstream& operator<<(std::ostringstream& os,
    const std::ostringstream& s) {
  os << s.str();
  return os;
}

template<typename T>
void log(std::ostringstream& os, const T& t) {
  os << t;
}

template<typename T, typename ... Args>
void log(std::ostringstream& os, const T& t, const Args &... args) {
  os << t;
  logger::log<Args...>(os, args...);
}

template<typename T, typename ... Args>
void log(sudoku::LoggerT<T>& logger, const char *file, uint32_t lineno,
    const char *function, const Args &... args) {

  static const std::string prefix(Utility::rpad(logger.get_prefix(), 5));

  std::ostringstream os;

  os << sudoku::Clocks::system_clock_as_string_ms()
      << " ["
      << thread_name
      << "]["
      << prefix
      << "]["
      << static_cast<void*>(&logger)
      << "] "
      << file
      << ":"
      << lineno
      << "("
      << function
      << ") ";

  logger::log<Args...>(os, args...);

  os << std::endl;

  logger.write(os.str());
}

}
}
}
}

//#define LOGALL(...)

#ifndef LOGALL
#define LOGALL(...) {                                                                  \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::All>::is_level_on())             \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::All> logger;   \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::All>                           \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}
#endif // LOGALL

//#define LOGDEV(...)

#ifndef LOGDEV
#define LOGDEV(...) {                                                                  \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::Dev>::is_level_on())             \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::Dev> logger;   \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::Dev>                           \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}
#endif // LOGDEV

#undef LOGDEV

#ifndef SUDOKU_LOGMACROS
#define SUDOKU_LOGMACROS
#define LOGDEBUG(...) {                                                                \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::Debug>::is_level_on())           \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::Debug> logger; \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::Debug>                         \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}

#define LOGERROR(...) {                                                                \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::Error>::is_level_on())           \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::Error> logger; \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::Error>                         \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}

#define LOGFATAL(...) {                                                                \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::Fatal>::is_level_on())           \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::Fatal> logger; \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::Fatal>                         \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}

#define LOGINFO(...) {                                                                 \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::Info>::is_level_on())            \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::Info> logger;  \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::Info>                          \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}

#define LOGTRACE(...) {                                                                \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::Trace>::is_level_on())           \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::Trace> logger; \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::Trace>                         \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}

#define LOGWARN(...) {                                                                 \
    if (cc::tools::sudoku::LoggerT<cc::tools::sudoku::Warn>::is_level_on())            \
    {                                                                                  \
      constexpr const char* basename(cc::tools::sudoku::system::basename(__FILE__));   \
      thread_local static cc::tools::sudoku::LoggerT<cc::tools::sudoku::Warn> logger;  \
      cc::tools::sudoku::logger::log<cc::tools::sudoku::Warn>                          \
      (logger, basename,                                                               \
          __LINE__, __FUNCTION__, __VA_ARGS__);                                        \
    }                                                                                  \
}
#endif // SUDOKU_LOGMACROS

#endif
