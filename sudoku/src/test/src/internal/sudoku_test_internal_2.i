std::pair<bool, const char*> internal_test2() {
  auto result (cc::tools::sudoku::Geometry::index_to_block(8));

  if (result == 2) {
    return {true, __FUNCTION__};
  }

  LOGERROR("got ", result);
  return {false, __FUNCTION__};
}

