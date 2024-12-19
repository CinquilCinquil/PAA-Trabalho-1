# PAA-Trabalho-1

## How to run?

You can either use the user interface with `python user_interface.py` or use the commands in the section below
(Obs: you might have to use `python3` in case you are in Linux):

### Commands
Compile: `g++ main.cpp -o main.exe`

Run a single test:
- **Windows**: `main.exe <algorithm> <folder_with_tests>`
- **Linux**: `./main.exe <algorithm> <folder_with_tests>`

Run all tests in a folder: `python run_tests.py <algorithm> <folder_with_tests>`

Group tests results in a folder into a single file: `python compose_test_results.py <folder_with_tests>`

### Examples:
**Windows**: `python run_tests.py DPLL test_cases\uf20-91` <br>
**Linux**: `python3 run_tests.py CIDPLL test_cases/uf20-91`

## How are the tests organized?

The test files are present in `test_cases` and the composed results are saved in `test_results`.

Each test outputs 6 parameters:
- name: the name of the test file;
- is_sat_result: the output of the algorithm (boolean);
- is_sat: whether the solution (string) satisfies the expression;
- is_correct: whether the boolean expression tested upon is satistiable or not *;
- solution: the string with the solution;
- time: the time it took for `DPLL` to execute in seconds.

(* Please ignore this field. All entries to this field have been set to `False` due to the large amount of time it takes for the exact algorithm `DPLL` to execute. However, it is worth noting that all tests in `test_cases\uf20-91` are known to be satisfiable, therefore the accuracy of the algorithm can be measured by the percentage of `True` outputs in is_sat_result)
