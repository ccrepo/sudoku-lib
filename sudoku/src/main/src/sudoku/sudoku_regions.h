#ifndef SUDOKU_REGIONS_H
#define SUDOKU_REGIONS_H

#include <array>
#include <cstdint>
#include <memory>

#include "sudoku_geometry.h"

namespace cc {
namespace tools {
namespace sudoku {

class Regions final {
private:
  static const std::shared_ptr<Regions> _regions;

public:
  static inline std::shared_ptr<Regions> get_regions() {
    return _regions;
  }

  ~Regions() {
  }

public:
  const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& get_block(
      const uint16_t block) const;

  const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& get_col(
      const uint16_t col) const;

  const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& get_row(
      const uint16_t row) const;

  inline const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>,
  Geometry::C_GEOMETRY_CELL_BUF_RCB>& get_blocks() const {
    return _blocks;
  }

  inline const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>,
  Geometry::C_GEOMETRY_CELL_BUF_RCB>& get_cols() const {
    return _cols;
  }

  inline const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>,
  Geometry::C_GEOMETRY_CELL_BUF_RCB>& get_rows() const {
    return _rows;
  }

private:
  Regions();

private:
  const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>,
  Geometry::C_GEOMETRY_CELL_BUF_RCB> _blocks;

  const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>,
  Geometry::C_GEOMETRY_CELL_BUF_RCB> _cols;

  const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>,
  Geometry::C_GEOMETRY_CELL_BUF_RCB> _rows;

private:
  Regions(const Regions&) = delete;
  Regions& operator=(const Regions&) = delete;

};

}
}
}

#endif
