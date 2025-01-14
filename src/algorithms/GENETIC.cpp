#ifndef GENETIC_file
#define GENETIC_file

#include "../Clause.cpp"
#include "DLIS.cpp"
#include "vector"

using sat_solution = std::tuple<bool, std::string>;
using population_t = std::pair<int, bool*>;

const int POP_SIZE = 200;
const double ELITISM_RATE = 0.5;
const int BEST_THRESHOLD = ELITISM_RATE*POP_SIZE;
const int ITERATION_LIMIT = 1200;

unsigned int seed_GENETIC;

void set_seed_GENETIC(int s) {
    seed_GENETIC = s;
}

bool comp(population_t &a, population_t &b) {
  if(a.first == b.first) return false;
  return a.first > b.first;
}

bool check_trivial_cases(ClauseSet *clause_set, std::string *solution) {
  int all_positive_clauses = 0;
  int all_negative_clauses = 0;
  for(auto &c : clause_set->clauses) {
    bool all_positive = true;
    bool all_negative = true;
    for(auto l : c.literals) {
      int var = std::get<0>(l);
      bool is_negated = std::get<1>(l);

      if(!is_negated) all_positive = false;
      else all_negative = false;
    }

    all_positive_clauses += all_positive;
    all_negative_clauses += all_negative;
  }

  if(all_negative_clauses == 0) {
    for(int i=1; i<=clause_set->variables.size(); i++) {
      solution->append(std::to_string(i));
      solution->push_back('T');
    }
    return true;
  } else if (all_positive_clauses == 0) {
    for(int i=1; i<=clause_set->variables.size(); i++) {
      solution->append(std::to_string(i));
      solution->push_back('F');
    }
    return true;
  }

  return false;
}


int fitness(bool *assignment, ClauseSet *clauses) {
  int result = 0;
  for(auto &c : clauses->clauses) {
    for(auto l : c.literals) {
      int var = std::get<0>(l);
      bool is_negated = std::get<1>(l);

      if(is_negated && !assignment[var]) {
        result++;
        break;
      } else if (!is_negated && assignment[var]) {
        result++;
        break;
      }
    }
  }
  return result;
}

void generate_first_generation(ClauseSet *clauses, population_t *population) {
  int n_variables = clauses->variables.size();

  for(int i=0; i<POP_SIZE; i++) {
    population[i].second = new bool[n_variables+1];
    for(int j=1; j<=n_variables; j++) {
      population[i].second[j] = rand() % 2;
    }
    population[i].first = fitness(population[i].second, clauses);
  }
}

std::string solution_to_string(bool *solution, int n_variables) {
  std::string s;
  for(int i=1; i<=n_variables; i++) {
    if(i != 1) s.push_back(' ');
    s.append(std::to_string(i));
    s.push_back(solution[i] ? 'T' : 'F');
  }
  return s;
}

void crossover(population_t &a, population_t &b, population_t &child, int n_variables) {
  for(int i=1; i<=n_variables; i++) {
     child.second[i] = (rand()&1 ?a.second[i] : b.second[i]);
  }
}

void mutate(population_t &p, ClauseSet *clauses) {
  int random_pos = (rand() % clauses->variables.size()) + 1;
  p.second[random_pos] = !p.second[random_pos];
  p.first = fitness(p.second, clauses);
}

void mutate_greedy(population_t &p, ClauseSet *clauses) {
  int n_variables = clauses->variables.size();
  int best_var = 1;
  int best_fit = 0;
  for(int i=1; i<=n_variables; i++) {
    p.second[i] = !p.second[i];
    int fit = fitness(p.second, clauses);
    p.second[i] = !p.second[i];

    if(fit > best_fit) {
      best_fit = fit;
      best_var = i;
    }
  }

  p.first = best_fit;
  p.second[best_var] = !p.second[best_var];
}

std::pair<int, int> roulette_wheel_selection_from_best(population_t* population, int* cumulative_fitness) {
  int total_fitness = cumulative_fitness[BEST_THRESHOLD-1];
  int random_selection = rand() % (total_fitness+1);
  int random_selection_2 = rand() % (total_fitness+1);

  int idx_first = std::lower_bound(cumulative_fitness, cumulative_fitness + BEST_THRESHOLD, random_selection) - cumulative_fitness;
  int idx_second = std::lower_bound(cumulative_fitness, cumulative_fitness + BEST_THRESHOLD, random_selection_2) - cumulative_fitness;

  return {idx_first, idx_second};
}

bool has_same_type_literals(ClauseSet* clause_set, int var, bool negative) {
  for(auto &c : clause_set->clauses) {
    for(auto l : c.literals) {
      int var_l = std::get<0>(l);
      bool is_negated = std::get<1>(l);

      if(var == var_l && is_negated != negative) {
        return false;
      }
    }
  }
  return true;
}

sat_solution GENETIC(ClauseSet *clause_set, std::string solution = "") {

  srand(seed_GENETIC);

  if(check_trivial_cases(clause_set, &solution)) {
    return {true, solution};
  }

  for(int i=1; i<=clause_set->variables.size(); i++) {
    if(has_same_type_literals(clause_set, i, true)) {
      clause_set = clause_set->apply(i, false);
    } else if (has_same_type_literals(clause_set, i, false)) {
      clause_set = clause_set->apply(i, true);
    }
  }


  int current_iteration = 0, last_improvement_iteration = 0;
  int best_fitting = 0;
  population_t current_generation[POP_SIZE];
  generate_first_generation(clause_set, current_generation);

  while(current_iteration - last_improvement_iteration < ITERATION_LIMIT) {
    sort(current_generation, current_generation + POP_SIZE, comp);

    if(current_generation[0].first == clause_set->clauses.size()) {
      return {true, solution_to_string(current_generation[0].second, clause_set->variables.size())};
    } else if (current_generation[0].first > best_fitting) {
      last_improvement_iteration = current_iteration;
      best_fitting = current_generation[0].first;
    }

    int cumulative_fitness[BEST_THRESHOLD];

    cumulative_fitness[0] = current_generation[0].first;
    for(int i=1; i<BEST_THRESHOLD; i++) {
      cumulative_fitness[i] = current_generation[i].first + cumulative_fitness[i-1];
    }

    for(int i=0; i<POP_SIZE-BEST_THRESHOLD; i++) {
      std::pair<int, int> parents = roulette_wheel_selection_from_best(current_generation, cumulative_fitness);
      crossover(current_generation[parents.first], current_generation[parents.second], current_generation[BEST_THRESHOLD+i], clause_set->variables.size());
      mutate(current_generation[BEST_THRESHOLD+i], clause_set);
    }

    current_iteration++;
  }

  for(int i=0; i<POP_SIZE; i++) {
    delete current_generation[i].second;
  }

  return {false, solution_to_string(current_generation[0].second, clause_set->variables.size())};
}

#endif