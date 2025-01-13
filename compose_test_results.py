"""
Unites all of the test results of a certain folder in a single file
"""

import os
import sys

def compose_test_results(alg, test_folder, repetitions):
    path = "test_results" + os.path.sep + "composed_results_" + alg + "_" + str(repetitions) + "rep_" + test_folder.replace("\\", "").replace("/", "_") + ".txt"
    os.makedirs(os.path.dirname(path), exist_ok=True)

    with open(path, 'w') as composed_result_file:
        composed_result_file.write("name, is_sat, evaluation, solution, time, seed\n")

        for f in os.listdir(test_folder):
            correct_alg = ("_" + alg + "_") in f or alg == ""
            if f.split(".")[-1] == "txt" and correct_alg:
                with open(test_folder + os.path.sep + f, 'r') as result_file:
                    for line in result_file.readlines():
                        composed_result_file.write(f + ", " + line)
    
    print("\nComposed test results saved in: ", path)

if __name__ == '__main__':
    if (len(sys.argv) == 4):
        compose_test_results(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        print("Error: not enough input values.")
