#ifndef TS_util
#define TS_util

#include <string>
#include <vector>
#include "Clause.cpp"

using bool_vec = std::vector<bool>;

std::string bool_vec_to_string(bool_vec arr) {
    std::string return_str = "";
    for (int i = 0;i < arr.size();i ++) {
        return_str += std::to_string(i) + (arr[i] ? "T" : "F") + " ";
    }
    return return_str;
}

bool_vec generate_arbitrary_solution(int n_vars) {

    bool_vec rnd_sol(n_vars);

    for (int i = 0;i < n_vars;i ++) {
        rnd_sol[i] = (rand() % 2) == 1;
    }

    return rnd_sol;
}

/*
std::vector<bool_vec> get_neighbour_solutions(bool_vec sol) {

    int n_solutions = 5;
    std::vector<bool_vec> solutions(n_solutions);

    for (int i = 0;i < n_solutions;i ++) {
        for (int j = 0;j < sol.size();j ++) {
            solutions[i].push_back(sol[j]);
            if (rand() % 4 <= 1)
                solutions[i][j] = !sol[j];
        }
    }

    return solutions;
}
*/

std::vector<bool_vec> get_neighbour_solutions(bool_vec sol) {

    int n_solutions = 5;
    std::vector<bool_vec> solutions(n_solutions);

    for (int i = 0;i < n_solutions;i ++) {
            bool_vec new_solution(sol.size());
            std::copy(sol.begin(), sol.end(), new_solution.begin());

            int a = rand() % sol.size();
            int b = rand() % sol.size();

            new_solution[a] = !new_solution[a];
            new_solution[b] = !new_solution[b];

            solutions[i] = new_solution;
        }

    return solutions;
}

bool_vec get_best_solution(ClauseSet * cs, std::vector<bool_vec> solutions) {

    bool_vec best_solution;
    int best_solution_quality = 0;

    for (bool_vec sol : solutions) {
        int sol_quality = evaluator(cs, bool_vec_to_string(sol));

        if (sol_quality > best_solution_quality) {
            best_solution_quality = sol_quality;
            best_solution = sol;
        }
    }

    return best_solution;
}

std::vector<int> get_move(bool_vec sol, bool_vec original_sol) {

    std::vector<int> move(sol.size());

    for (int i = 0;i < sol.size();i ++) {
        move[i] = sol[i] != original_sol[i];
    }
    return move;
}

bool in_taboo_list(std::vector<int> move, std::vector<std::vector<int>> TL) {
    return std::find(TL.begin(), TL.end(), move) != TL.end();
}

#endif
