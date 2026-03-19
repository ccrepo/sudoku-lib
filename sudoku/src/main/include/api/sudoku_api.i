
%module sudoku_jlib

%{
#include "sudoku_api.h"
%}

%include "carrays.i"
%include "stdint.i"

%array_functions(uint8_t, uint8Array);

%include "typemaps.i"

%apply int *OUTPUT { int *out_runtime };

%include "sudoku_api.h"
