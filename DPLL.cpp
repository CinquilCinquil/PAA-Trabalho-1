#ifndef DPLL
#define DPLL_file

#include "Clause.cpp"
#include "DLIS.cpp"

bool DPLL(ClauseSet * clause_set) {

    if (clause_set->has_empty_clause()) return false;

    if (clause_set->clauses.size() == 0) return true;

    int unit_clause_var;
    if (clause_set->has_unit_clause(&unit_clause_var)) {
        return DPLL(clause_set->apply(unit_clause_var, true));
    }

    // pure literal case?

    int new_var = DLIS(clause_set);

    if (DPLL(clause_set->apply(new_var, false))) return true;

    return DPLL(clause_set->apply(new_var, true));
}

#endif