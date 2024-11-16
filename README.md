# PAA-Trabalho-1

## How to run?

You can either use the user interface with `python user_interface.py` or use the commands in the section below
(Obs: you might have to use `python3` in case you are in Linux):

### Commands
Compile: `g++ main.cpp -o main.exe`

Run a single test:
- **Windows**: `main.exe <folder_with_tests>`
- **Linux**: `./main.exe <folder_with_tests>`

Run all tests in a folder: `python run_tests.py <folder_with_tests>`

Group tests results in a folder into a single file: `python compose_test_results.py <folder_with_tests>`

### Examples:
**Windows**: `python run_tests.py test_cases\uf20-91` <br>
**Linux**: `python3 run_tests.py test_cases/uf20-91`