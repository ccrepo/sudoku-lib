std::pair<bool, const char*> external_test2() {

  const auto& request(cc::tools::sudoku::test::TestPosition::get_any_position());

  std::cout << "request: "
      << std::endl
      << request
      << std::endl
      << std::endl;

  uint8_t response[L_CONST_RESULT_BUFFER_SIZE];
  memset(response, 0, L_CONST_RESULT_BUFFER_SIZE);

  int32_t runtime(0);

  if (get_sudoku_possible_moves_STUB(request.c_str(), response, &runtime)) {

    std::cout << "NOT ok"
        << std::endl;

    return {false, __FUNCTION__};
  }

  std::cout << "ok"
      << std::endl
      << std::endl;

  std::cout << "response: "
      << std::endl
      << response
      << std::endl
      << std::endl;

  std::cout << "runtime: "
      << std::endl
      << std::to_string(runtime)
      << "ms"
      << std::endl
      << std::endl;

  return {true, __FUNCTION__};
}
