#ifndef DPLL_file
#define DPLL_file

#include "Clause.cpp"
#include "DLIS.cpp"

using sat_solution = std::tuple<bool, std::string>;

sat_solution heuristic_DPLL(ClauseSet * clause_set, std::string solution = "") {

    if (clause_set->has_empty_clause()) return sat_solution(false, solution);

    if (clause_set->clauses.size() == 0) return sat_solution(true, solution);

    literal unit_clause_literal;
    if (clause_set->has_non_negated_unit_clause(&unit_clause_literal)) {
        int unit_clause_var = std::get<0>(unit_clause_literal);
        return heuristic_DPLL(clause_set->apply(unit_clause_var, true), solution + std::to_string(unit_clause_var) + "T ");
    }

    int new_var = DLIS(clause_set);
    bool value = clause_set->has_greater_positive_occurences(new_var);
    if (value) {
        return heuristic_DPLL(clause_set->apply(new_var, true), solution + std::to_string(new_var) + "T ");
    }

    return heuristic_DPLL(clause_set->apply(new_var, false), solution + std::to_string(new_var) + "F ");
}

sat_solution DPLL(ClauseSet * clause_set, std::string solution = "") {

    if (clause_set->has_empty_clause()) return sat_solution(false, solution);

    if (clause_set->clauses.size() == 0) return sat_solution(true, solution);

    literal unit_clause_literal;
    if (clause_set->has_non_negated_unit_clause(&unit_clause_literal)) {
        int unit_clause_var = std::get<0>(unit_clause_literal);
        return DPLL(clause_set->apply(unit_clause_var, true), solution + std::to_string(unit_clause_var) + "T ");
    }

    int new_var = DLIS(clause_set);

    auto dpll_return = DPLL(clause_set->apply(new_var, false), solution + std::to_string(new_var) + "F ");
    if (std::get<0>(dpll_return)) return sat_solution(true, std::get<1>(dpll_return));
    return DPLL(clause_set->apply(new_var, true), solution + std::to_string(new_var) + "T ");
}

#endif