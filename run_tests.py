"""
Runs the sat solver in all .cnf files of a specified folder
"""

import os
import sys
import subprocess

def run_tests(test_folder):
    run_main = "./main.exe"
    if os.name == 'nt':
        run_main = "main.exe"

    for f in os.listdir(test_folder):
        if f.split(".")[-1] == "cnf":
            command = [run_main, os.path.join(test_folder, f)]
            subprocess.run(command, shell=False)

if __name__ == '__main__':
    if (len(sys.argv) > 1):
        run_tests(sys.argv[1])
    else:
        print("Error: please specify the path to the test folder.")