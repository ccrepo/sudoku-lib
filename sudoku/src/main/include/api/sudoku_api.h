#ifndef SUDOKU_API_H
#define SUDOKU_API_H

#include <cstdint>

extern "C" const int32_t L_CONST_RESULT_BUFFER_SIZE;

extern "C" int32_t get_sudoku_solution_STUB(const char* in_request,
    uint8_t* out_response,
    int32_t* out_runtime);

extern "C" int32_t get_sudoku_possible_moves_STUB(const char* in_request,
    uint8_t* out_response,
    int32_t* out_runtime);

extern "C" int32_t get_sudoku_random_board_STUB(uint8_t* out_response,
    int32_t* out_runtime);

#endif
