import os
import sys
import subprocess
from run_tests import run_tests
from compose_test_results import compose_test_results

subprocess.run(["g++", "main.cpp", "-o", "main.exe"], shell=False)

print("\n### WELCOME ###\n")
print("This is a menu where you can execute tests with the CIDPLL algorithm.\n")

while True:
    print("Type:\n")
    print("   1 to run all tests files on a folder;\n")
    print("   2 to run a single test file;\n")
    print("   3 exit.\n")
    selected_option = int(input("Input: "))

    if selected_option == 1:
        filepath = input("Please enter the path to the folder containing tests: ")
        run_tests(filepath)
        compose_test_results(filepath)
        print("All finished")
    elif selected_option == 2:
        filepath = input("Please enter the path to the test file: ")
        
        run_main = "./main.exe"
        if os.name == 'nt':
            run_main = "main.exe"

        command = [run_main, filepath]

        subprocess.run(command, shell=False)
    elif selected_option == 3:
        break
    else:
        print("Invalid input!")
        
    print("\n")