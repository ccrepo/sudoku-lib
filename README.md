# Project: Sudoku-lib

Project Sudoku-lib implements a sudoku problem solver.

Sudoku-lib does not maintain state and has been developed for Linux. 

All code, excepting the SWIG components, also work on macOS (x86) but this operation on that platform has not been fully tested.

Sudoku-lib currently exposes two methods.

## Internals

Sudoku-lib is implemented in C++. 

Sudoku-lib is multi-threaded, although no more than a single thread can process a given Game at any one time.

Internally a Game is defined as a board position (with an associated move history list). 

During "possible next moves" processing the user supplied Game is split into multiple sub-Games which are allocated to seperate threads. 

Each Game in this sub-Games group differs from each other by exactly one move.

A possible enhancement is that this design coould, in principle, be generalised to all Game processing. 

We could add logic to split all Games dynamically at any level in the search into sub-Games and then combine the sub-results on the way up.

We would only need to keep the fastest sub-result, as we only need one sub-Game to succeed to mark an entire branch as possible. 

## Methods 

1. get_sudoku_solution_STUB

    Method: get_sudoku_solution_STUB finds a solution for a sudoku position, if possible. 
    
    It returns the solutions moves and the final solved board to the caller. 
    
    If no solution is found it only returns an error message.

    ```cpp
    unsigned int32_t get_sudoku_solution_STUB(
			const char* in_request,
			uint8_t* out_response,
			int32_t* out_runtime);
    ```

2. get_sudoku_possible_moves_STUB

    Method: get_sudoku_possible_moves_STUB finds all possible valid next moves for a given sudoku position. 
    
    It then returns a list of these moves to the caller. 

    ```cpp
    unsigned int32_t get_sudoku_possible_moves_STUB(
			const char* in_request,
			uint8_t* out_response,
			int32_t out_runtime);
    ```
    
## Usage

1. Pre-requisites:

    Software:
    
    Build and Run
    
    ```text
    Linux (Ubuntu 22.04.2 LTS (Jammy Jellyfish)).
    Gcc version 11.3.0.
    Open JDK version 19.0.2.
    ```
    
    Develop
    
    ```text
    SWIG 4.1
    ```
    
2. Build:

    Navigate to project home directory and execute the following commands

    ```bash
    cd $projectDir
    ./gradlew clean
    ./gradlew build
    ```
    
    The build creates a shared lib located at $projectDir/lib/build/lib/main/debug/linux/

3. Helper Scripts

    There are helper scripts in the $projectDir/bin directory
    
    ```text
    projectDir/bin/c:  compile clean, build and run tests.
    projectDir/bin/b:  run script 'c' with pagination.
    projectDir/bin/jm: test get_sudoku_possible_moves_STUB via java example code.
    projectDir/bin/js: test get_sudoku_solution_STUB via java example code.
    projectDir/bin/m:  parse logfile from script 't' and summarise return code counts.
    projectDir/bin/r:  re-run tests.
    projectDir/bin/s:  run SWIG JNI layer generation. only on linux.
    projectDir/bin/t:  run c++ tests in endless loop and log return codes.
    ```

4. Development:

    An example C++ client and two Java test clients are included in this project.
    
    The C++ code is located in directory 
    
        $projectDir/sudoku/src/test/src/lib/
    
        see file: 
    
            sudoku_libtest.cpp
    
    The Java code is located in directory 
    
        $projectDir/sudoku/src/test/src/java      
    
        see files: 
        
            sudoku_libclient_moves.java
        
            sudoku_libclient_solution.java
        
5. Planned Changes:

    SWIG:
        
        Replace SWIG with JNI or faster solution

