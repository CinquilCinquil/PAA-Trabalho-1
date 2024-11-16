#ifndef DLIS_file
#define DLIS_file

#include "Clause.cpp"

/**
 * Returns the variable with most occurences in a clause set.
 */
int DLIS(ClauseSet * clause_set) {

    int max_f = 0;
    int max_variable = -1;

    for (int variable : clause_set->variables) {

        int f_sum = 0;
        int n = clause_set->longest_clause_size();

        for (int k = 1;k <= n;k ++) {
            f_sum += clause_set->count_clauses_containing_var_with_specified_size(variable, k);
        }

        if (f_sum > max_f) {
            max_f = f_sum;
            max_variable = variable;
        }
    }

    return max_variable;

}

#endif