#ifndef DLIS_file
#define DLIS_file

#include "Clause.cpp"

int DLIS(ClauseSet * clause_set) {

    int max_f = 0;
    int max_variable = -1;

    for (int variable : clause_set->variables) {

        int f_sum = 0;
        int n = clause_set->longest_clause_size();

        for (int k = 0;k < n;k ++) {
            f_sum += clause_set->clauses_with_var(variable, k);
        }

        if (f_sum > max_f) {
            max_f = f_sum;
            max_variable = variable;
        }
    }

    return max_variable;

}

#endif