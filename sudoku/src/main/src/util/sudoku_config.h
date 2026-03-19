#ifndef SUDOKU_CONFIG_H
#define SUDOKU_CONFIG_H

#include "sudoku_log.h"
#include "sudoku_system.h"
#include "sudoku_utility.h"

namespace cc {
namespace tools {
namespace sudoku {

class Config final {

private:
  Config() :
    _level(
        Utility::to_lowercase(
            Utility::trim(system::getenv(Logger::C_LOGGER_LEVEL)))) {
  }

  inline const std::string& level() const {
    return _level;
  }

public:
  ~Config() {
  }

  static inline std::shared_ptr<Config> get_config() {
    static std::shared_ptr<Config> _config(new Config());

    return _config;
  }

  inline bool is_log_debug() const {
    static const bool level(this->level() == Logger::C_LOGGER_LEVEL_DEBUG);
    return level;
  }

  inline bool is_log_error() const {
    static const bool level(this->level() == Logger::C_LOGGER_LEVEL_ERROR);
    return level;
  }

  inline bool is_log_fatal() const {
    static const bool level(this->level() == Logger::C_LOGGER_LEVEL_FATAL);
    return level;
  }

  inline bool is_log_info() const {
    static const bool level(this->level() == Logger::C_LOGGER_LEVEL_INFO);
    return level;
  }

  inline bool is_log_trace() const {
    static const bool level(this->level() == Logger::C_LOGGER_LEVEL_TRACE);
    return level;
  }

  inline bool is_log_all() const {
    static const bool level(this->level() == Logger::C_LOGGER_LEVEL_ALL);
    return level;
  }

  inline bool is_log_warn() const {
    static const bool level(this->level() == Logger::C_LOGGER_LEVEL_WARN);
    return level;
  }

  bool is_no_level();

private:
  Config(const Config&) = delete;
  Config& operator=(const Config&) = delete;

private:
  const std::string _level;

};

}
}
}

#endif

