"""
Unites all of the test results of a certain folder in a single file
"""

import os
import sys

def compose_test_results(test_folder):
    path = "test_results" + os.path.sep + "composed_results_" + test_folder.replace("\\", "").replace("/", "") + ".txt"
    os.makedirs(os.path.dirname(path), exist_ok=True)

    with open(path, 'w') as composed_result_file:
        composed_result_file.write("name, is_sat_result, is_sat, is_correct, solution, time\n")

        for f in os.listdir(test_folder):
            if f.split(".")[-1] == "txt":
                with open(test_folder + os.path.sep + f, 'r') as result_file:
                    composed_result_file.write(f + ", " + result_file.readline() + "\n")
    
    print("\nComposed test results saved in: ", path)

if __name__ == '__main__':
    if (len(sys.argv) > 1):
        compose_test_results(sys.argv[1])
    else:
        print("Error: please specify the path to the test folder.")
