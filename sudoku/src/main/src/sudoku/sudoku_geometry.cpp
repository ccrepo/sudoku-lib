#include "sudoku_geometry.h"

namespace cc {
namespace tools {
namespace sudoku {

inline std::array<uint16_t, Geometry::C_GEOMETRY_TOTAL_CELLS> Geometry::index_to_region(
    const std::function<uint16_t(uint16_t)>& f) {

  std::array<uint16_t, Geometry::C_GEOMETRY_TOTAL_CELLS> buffer { };

  for (uint16_t i(0); i < Geometry::C_GEOMETRY_TOTAL_CELLS; ++i) {
    buffer[i] = f(i);
  }

  return buffer;
}

}
}
}
