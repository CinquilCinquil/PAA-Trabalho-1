import os
import sys
import subprocess
from run_tests import run_tests
from compose_test_results import compose_test_results

subprocess.run(["g++", "main.cpp", "-o", "main.exe"], shell=False)

print("\n### WELCOME ###\n")
print("This is a menu where you can execute tests with the available SAT solvers.\n")

current_alg = "CIDPLL"

while True:
    print("Type:\n")
    print("   1 to run all tests files on a folder;\n")
    print("   2 to run a single test file;\n")
    print(f"   3 to switch the algorithm. The current one is {current_alg};\n")
    print("   4 exit.\n")
    selected_option = int(input("Input: "))

    if selected_option == 1:
        filepath = input("Please enter the path to the folder containing tests: ")
        run_tests(current_alg, filepath)
        compose_test_results(current_alg, filepath)
        print("All finished")
    elif selected_option == 2:
        filepath = input("Please enter the path to the test file: ")
        
        run_main = "./main.exe"
        if os.name == 'nt':
            run_main = "main.exe"

        command = [run_main, current_alg, filepath]

        subprocess.run(command, shell=False)
    elif selected_option == 3:
        select_alg = int(input("Type 1 for CIDPLL or 2 for DPLL: "))
        current_alg = "CIDPLL" if select_alg == 1 else "DPLL"
    elif selected_option == 4:
        break
    else:
        print("Invalid input!")
        
    print("\n")