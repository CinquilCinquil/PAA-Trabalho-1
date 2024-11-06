"""
Runs the sat solver in all .cnf files of a specified folder
"""

import os
import sys
import subprocess

if (len(sys.argv) > 1):

    test_folder = sys.argv[1]
    run_main = "./main.exe"
    if os.name == 'nt':
        run_main = "main.exe"

    for f in os.listdir(test_folder):
        if f.split(".")[-1] == "cnf":
            command = [run_main, os.path.join(test_folder, f)]
            subprocess.run(command, shell=True)
else:
    print("Error: please specify the path to the test folder.")
