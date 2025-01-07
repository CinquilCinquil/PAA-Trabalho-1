#ifndef TS_file
#define TS_file

#include <stdlib.h>
#include "Clause.cpp"
#include "TS_util.cpp"

using sat_answer = std::tuple<bool, std::string>;
using bool_vec = std::vector<bool>;

unsigned int seed;

void set_seed_TS(int s) {
    seed = s;
}

sat_answer TS(ClauseSet * clause_set, std::string str = "") {

    srand(seed);

    int n_vars = clause_set->variables.size();

    int iter = 0, bestiter = 0, maxiter = 1000;
    std::vector<std::vector<int>> TL;
    bool_vec sol = generate_arbitrary_solution(n_vars);
    int sol_quality = evaluator(clause_set, bool_vec_to_string(sol));

    while (iter - bestiter < maxiter) {
        iter ++;
        std::vector<bool_vec> solutions = get_neighbour_solutions(sol);
        bool_vec best_solution = get_best_solution(clause_set, solutions);
        std::string best_solution_string = bool_vec_to_string(best_solution);
        
        if (verifier(clause_set, best_solution_string)) {

            return sat_answer(true, best_solution_string);

        } else {
            std::vector<int> move = get_move(best_solution, sol);

            if (!in_taboo_list(move, TL)) {

                int new_solution_quality = evaluator(clause_set, best_solution_string);
                if (new_solution_quality > sol_quality) {
                    sol_quality = new_solution_quality;
                    sol = best_solution;
                    bestiter = iter;
                }

                TL.push_back(move);
            }
        }
    }

    return sat_answer(false, bool_vec_to_string(sol));
}


#endif