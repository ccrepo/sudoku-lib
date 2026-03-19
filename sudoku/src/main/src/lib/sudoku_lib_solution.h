#ifndef SUDOKU_LIB_SOLUTION_H
#define SUDOKU_LIB_SOLUTION_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "sudoku_api.h"

#include "sudoku_lib_codes.h"

namespace cc {
namespace tools {
namespace sudoku {

class Router;

namespace lib {

class Solution final {

public:
  Solution(const std::string& request);

  ~Solution() {
  }

  uint32_t get_sudoku_solution(
      std::vector<std::pair<uint16_t, uint16_t>>& out_moves,
      int32_t& out_runtime);

private:
  const std::string _request;
  const std::weak_ptr<Router> _router;

private:
  Solution(const Solution&) = delete;
  Solution operator=(const Solution&) = delete;

};


}
}
}
}

#endif
