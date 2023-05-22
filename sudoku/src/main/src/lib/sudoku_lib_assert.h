#ifndef SUDOKU_LIB_ASSERT_H
#define SUDOKU_LIB_ASSERT_H

#include <csignal>

namespace cc {
namespace tools {
namespace sudoku {
namespace lib {

static_assert(sizeof(char) == 1, "this code assumes that char is 1 byte.");
static_assert(sizeof(int)  == 4, "this code assumes that integer is 4 bytes.");
static_assert(sizeof(long) == 8, "this code assumes that long is 8 bytes.");

static_assert(sizeof(unsigned char) == 1, "this code assumes that unsigned char is 1 byte.");
static_assert(sizeof(unsigned int)  == 4, "this code assumes that unsigned integer is 4 bytes.");
static_assert(sizeof(unsigned long) == 8, "this code assumes that unsigned long is 8 bytes.");

}
}
}
}

#endif
