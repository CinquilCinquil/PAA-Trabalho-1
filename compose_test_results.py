"""
Unites all of the test results of a certain folder in a single file
"""

import os
import sys

if (len(sys.argv) > 1):

    test_folder = sys.argv[1]

    path = "test_results" + os.path.sep + "composed_results.txt"
    os.makedirs(os.path.dirname(path), exist_ok=True)

    with open(path, 'w') as composed_result_file:
        composed_result_file.write("name, is_sat, solution, time\n")

        for f in os.listdir(test_folder):
            if f.split(".")[-1] == "txt":
                with open(test_folder + os.path.sep + f, 'r') as result_file:
                    composed_result_file.write(f + ", " + result_file.readline() + "\n")
                
else:
    print("Error: please specify the path to the test folder.")
