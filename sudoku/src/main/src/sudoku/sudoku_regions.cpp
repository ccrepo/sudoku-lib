#include "sudoku_regions.h"
#include "sudoku_geometry.h"

namespace cc {
namespace tools {
namespace sudoku {
namespace regions {

namespace row {
std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> create_row(const uint16_t row) {
  std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> buffer {};

  for (uint16_t i(0), base(row * Geometry::C_GEOMETRY_BOARD_SIZE);
      i < Geometry::C_GEOMETRY_BOARD_SIZE;
      ++i) {
    buffer[i] = base + i;
  }

  return buffer;
}

static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r0(create_row(0));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r1(create_row(1));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r2(create_row(2));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r3(create_row(3));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r4(create_row(4));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r5(create_row(5));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r6(create_row(6));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r7(create_row(7));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> r8(create_row(8));

const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>, Geometry::C_GEOMETRY_CELL_BUF_RCB> rows {
  r0,
  r1,
  r2,
  r3,
  r4,
  r5,
  r6,
  r7,
  r8
};
}

namespace col {

std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> create_col(const uint16_t col) {
  std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> buffer {};

  for (uint16_t i(0), base(col);
      i < Geometry::C_GEOMETRY_BOARD_SIZE;
      ++i) {
    buffer[i] = base + (i * Geometry::C_GEOMETRY_BOARD_SIZE);
  }

  return buffer;
}

static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c0(create_col(0));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c1(create_col(1));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c2(create_col(2));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c3(create_col(3));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c4(create_col(4));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c5(create_col(5));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c6(create_col(6));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c7(create_col(7));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> c8(create_col(8));

const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>, Geometry::C_GEOMETRY_CELL_BUF_RCB> cols {
  c0,
  c1,
  c2,
  c3,
  c4,
  c5,
  c6,
  c7,
  c8
};

}

namespace block {

std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> create_block(const uint16_t block) {
  std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> buffer {};

  for (uint16_t i(0), j(0);
      i <= Geometry::C_GEOMETRY_CELL_MAX_INDEX;
      ++i) {
    if (Geometry::index_to_block(i) == block) {
      buffer[j++] = i;
    }
  }

  return buffer;
}

static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b0(create_block(0));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b1(create_block(1));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b2(create_block(2));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b3(create_block(3));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b4(create_block(4));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b5(create_block(5));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b6(create_block(6));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b7(create_block(7));
static const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB> b8(create_block(8));

const std::array<const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>, Geometry::C_GEOMETRY_CELL_BUF_RCB> blocks {
  b0,
  b1,
  b2,
  b3,
  b4,
  b5,
  b6,
  b7,
  b8
};
}

}

const std::shared_ptr<Regions> Regions::_regions(new Regions());

Regions::Regions() :
				    _blocks(regions::block::blocks),
				    _cols(regions::col::cols),
				    _rows(regions::row::rows) {
}

const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& Regions::get_block(
    const uint16_t block) const {

  if (block >= Geometry::C_GEOMETRY_BOARD_SIZE) {
    throw std::out_of_range("block invalid " + std::to_string(block));
  }

  return _blocks[block];
}

const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& Regions::get_col(
    const uint16_t col) const {

  if (col >= Geometry::C_GEOMETRY_BOARD_SIZE) {
    throw std::out_of_range("col invalid " + std::to_string(col));
  }

  return _cols[col];
}

const std::array<uint16_t, Geometry::C_GEOMETRY_CELL_BUF_RCB>& Regions::get_row(
    const uint16_t row) const {

  if (row >= Geometry::C_GEOMETRY_BOARD_SIZE) {
    throw std::out_of_range("row invalid " + std::to_string(row));
  }

  return _rows[row];
}

}
}
}

