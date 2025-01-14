import os
import sys
import subprocess
from run_tests import run_tests
from compose_test_results import compose_test_results
from process_test_results import process_test_results

subprocess.run(["g++", os.path.join("src", "main.cpp"), "-o", "main.exe"], shell=False)

print("\n### WELCOME ###\n")
print("This is a menu where you can execute tests with the available SAT solvers.\n")

current_alg = "CIDPLL"
repetitions = 5

while True:
    print("Type:\n")
    print("   1 to run all tests files on a folder;\n")
    print("   2 to run a single test file;\n")
    print(f"   3 to switch the algorithm. The current one is {current_alg};\n")
    print("   4 to run all tests available;\n")
    print("   5 exit.\n")
    selected_option = int(input("Input: "))

    if selected_option == 1:
        filepath = input("Please enter the path to the folder containing tests: ")
        print(f"running with {repetitions} repetitions");
        run_tests(current_alg, filepath, repetitions)
        compose_test_results(current_alg, filepath, repetitions)
        print("All finished")
    elif selected_option == 2:
        filepath = input("Please enter the path to the test file: ")
        
        run_main = "./main.exe"
        if os.name == 'nt':
            run_main = "main.exe"

        command = [run_main, current_alg, filepath, "./test_results"]

        subprocess.run(command, shell=False)
    elif selected_option == 3:
        select_alg = int(input("Type 1 for CIDPLL, 2 for DPLL, 3 for GENETIC and 4 for TABOO SEARCH: "))
        algorithms = ["CIDPLL", "DPLL", "GENETIC", "TS"]
        current_alg = algorithms[select_alg-1]
    elif selected_option == 4:
        folders = ["uf20-91", "uf50-218", "uf125-538"]
        for fold in folders:
            run_tests(current_alg, os.path.join("test_cases", fold), repetitions)
            compose_test_results(current_alg, os.path.join("test_cases", fold), repetitions)
        process_test_results(current_alg, repetitions)

    elif selected_option == 5:
        break;
    else:
        print("Invalid input!")
        
    print("\n")