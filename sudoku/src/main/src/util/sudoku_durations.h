#ifndef SUDOKU_DURATIONS_H
#define SUDOKU_DURATIONS_H

namespace cc {
namespace tools {
namespace sudoku {

class Durations final {

public:

  static constexpr uint16_t C_DURATIONS_MINIMUM   { 5 };
  static constexpr uint16_t C_DURATIONS_MINISCULE { 10 };
  static constexpr uint16_t C_DURATIONS_SHORTEST  { 25 };
  static constexpr uint16_t C_DURATIONS_SHORTER   { 50 };
  static constexpr uint16_t C_DURATIONS_SHORT     { 75 };
  static constexpr uint16_t C_DURATIONS_MEDIUM    { 100 };
  static constexpr uint16_t C_DURATIONS_LONG      { 200 };
  static constexpr uint16_t C_DURATIONS_LONGER    { 400 };
  static constexpr uint16_t C_DURATIONS_LONGEST   { 500 };

private:
  Durations() = delete;
  ~Durations() = delete;
  Durations(const Durations&) = delete;
  Durations& operator=(const Durations&) = delete;

};

}
}
}

#endif
