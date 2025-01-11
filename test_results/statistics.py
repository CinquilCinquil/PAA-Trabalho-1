a = open("composed_results_TS_5rep_test_cases_uf50-218.txt", 'r')
b = open("processed_results_TS_5rep_test_cases_uf50-218.txt", 'w')
b.write("name, is_sat, evaluation, time\n")

lines = a.readlines()
lines.pop(0)
a.close()

total_guess = 0
total_distance = 0
total_time = 0
name = "x"
n = 5

for i in range(len(lines)):

    name, guess, distance, solution, time, seed = lines[i].split(", ")

    total_guess += int(guess)
    total_distance += int(distance)
    total_time += float(time)

    if (i % n == n - 1):
        b.write(name + ", " + str(round(total_guess/n, 2)) + ", " + str(round(total_distance/n, 2)) + ", " + str(round(total_time/n, 6)) + "\n")
        total_guess = 0
        total_distance = 0
        total_time = 0

b.close()