"""
Runs a sat solver in all .cnf files of a specified folder
"""

import os
import sys
import subprocess

def run_tests(alg, test_folder):
    run_main = "./main.exe"
    if os.name == 'nt':
        run_main = "main.exe"

    for f in os.listdir(test_folder):
        if f.split(".")[-1] == "cnf":
            command = [run_main, alg, os.path.join(test_folder, f)]
            subprocess.run(command, shell=False)

if __name__ == '__main__':
    if (len(sys.argv) == 3):
        run_tests(sys.argv[1], sys.argv[2])
    else:
        print("Error: not enough input values.")