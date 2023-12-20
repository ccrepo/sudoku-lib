std::pair<bool, const char*> internal_test1() {
  auto result (cc::tools::sudoku::Geometry::index_to_row(27));

  if (result == 3) {
    return {true, __FUNCTION__};
  }

  LOGERROR("got ", result);
  return {false, __FUNCTION__};
}

