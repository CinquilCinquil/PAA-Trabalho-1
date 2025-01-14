import os
import sys
N_VARIABLES=0;
N_CLAUSES=1;

V_DISTANCE=0;
V_GUESS=2;


def substring_from_chars(a, b, text):
  pos_inicio = text.find(a)
  pos_fim = text.find(b)
  return text[pos_inicio + 1 : pos_fim].strip()

def process_test_results(algorithm, repetitions):
  instances = [[20, 91], [50, 218], [125, 538]]
  output_file_path = os.path.join("test_results", f"processed_results_{algorithm}_{repetitions}rep.txt")
  output_file = open(output_file_path, 'w');

  output_file.write("variables,clauses,average time,average % worse than the optimal,correct %\n")
  for instance in instances:
    composed_results_path = os.path.join(
      "test_results", 
      f"composed_results_{algorithm}_{repetitions}rep_test_cases_uf{instance[N_VARIABLES]}-{instance[N_CLAUSES]}.txt"
    )

    composed_results_file = open(composed_results_path, 'r')
    lines = composed_results_file.readlines();

    best_solution = dict();

    total_time = 0
    total_correct = 0
    total_percent = 0

    for index,line in enumerate(lines):
      if(index == 0): continue;

      name, guess, distance, solution, time, seed = line.split(", ")
      # print(distance)
      if not best_solution.__contains__(name):
        best_solution[name] = (int(distance), float(time), int(guess));
      elif best_solution[name][V_DISTANCE] < int(distance):
        best_solution[name] = (int(distance), float(time), int(guess));
      total_time += float(time)

    file = open(f"test_results/extra_{algorithm}_uf{instance[N_CLAUSES]}-{instance[N_VARIABLES]}.txt", 'w')
    file.write("#id, distance\n")
    for name in best_solution:
      solution = best_solution[name]
      total_correct += solution[V_GUESS];
      total_percent += float((instance[N_CLAUSES]-solution[V_DISTANCE])/instance[N_CLAUSES]);
      file.write(f"{int(substring_from_chars('-', '_', name))}, {solution[V_DISTANCE]}\n");
    file.close();

    average_time = total_time/(len(best_solution)*int(repetitions))
    average_percentage = total_percent/len(best_solution)
    average_correctness = total_correct/len(best_solution)

    output_file.write(f"{instance[N_VARIABLES]}, {instance[N_CLAUSES]}, {average_time}, {average_percentage}, {average_correctness}\n")
  
  output_file.close()


"""
usage: [ALGORITHM] [REPETITIONS]
"""
if __name__ == '__main__':
    if len(sys.argv) < 3: 
      print("Not enough arguments")
    else: 
      process_test_results(sys.argv[1], sys.argv[2])
