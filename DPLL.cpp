#ifndef DPLL_file
#define DPLL_file

#include "Clause.cpp"
#include "DLIS.cpp"

bool DPLL(ClauseSet * clause_set) {

    if (clause_set->has_empty_clause()) return false;

    if (clause_set->clauses.size() == 0) return true;

    literal unit_clause_literal;
    if (clause_set->has_unit_clause(&unit_clause_literal)) {
        int unit_clause_var = std::get<0>(unit_clause_literal);
        bool negated = std::get<1>(unit_clause_literal);
        return DPLL(clause_set->apply(unit_clause_var, !negated));
    }

    // pure literal case?

    int new_var = DLIS(clause_set);

    if (DPLL(clause_set->apply(new_var, false))) return true;

    return DPLL(clause_set->apply(new_var, true));
}

#endif