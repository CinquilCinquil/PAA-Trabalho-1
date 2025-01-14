# PAA-Trabalho-3

## How to run?

You can either use the user interface with `python user_interface.py` or use the commands in the section below
(Obs: you might have to use `python3` in case you are in Linux):

### Commands
Compile:
- **Windows**: `g++ src\main.cpp -o main.exe -O3 -std=c++17`
- **Linux**:  `g++ src/main.cpp -o main.exe -O3 -std=c++17`

Run a single test:
- **Windows**: `main.exe <algorithm> <file> <outputfile> <repetitions>`
- **Linux**: `./main.exe <algorithm> <file> <outputfile> <repetitions>`

Run all tests in a folder: `python run_tests.py <algorithm> <folder_with_tests> <repetitions>`

Group tests results in a folder into a single file: `python compose_test_results.py <algorithm> <folder_with_tests> <repetitions>`

### Examples
- **Windows**: `python run_tests.py GENETIC test_cases\uf20-91 5` <br>
- **Linux**: `python3 run_tests.py TS test_cases/uf20-91 5`

## How are the tests organized?

The test files are present in `test_cases` and the results are saved in `test_results`.

Each test outputs 5 parameters:
- name: the name of the test file;
- is_sat: whether the solution (string) satisfies the expression;
- solution: the string with the solution;
- time: the time it took for the algorithm to execute in seconds.
- seed: the seed for randomized functions used by the algorithm