#ifndef CLAUSE
#define CLAUSE

#include <tuple>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <sstream>

using literal = std::tuple<int, bool>; /*<variable id, whether it is negated> */
using StringClause = std::vector<std::vector<std::string>>;

class Clause {
public:
    std::vector<literal> literals;

    int size() {
        return literals.size();
    }

    void print() {
        std::cout << '{';
        for (literal l : literals) {
            std::cout << (std::get<1>(l) ? "-" : "")  << std::get<0>(l) << ", ";
        }
        std::cout << '}';
    }
};

class ClauseSet {
public:
    std::vector<int> variables;
    std::vector<Clause> clauses;

    ClauseSet() {};

    /**
     * Makes a clause set from a list of strings.
     * {{"x"}, {"-x", "y"}, {"-y"}} represents the expression
     * (x) AND (NOT x OR y) AND (NOT y)
     */
    ClauseSet(StringClause clause_in_string) {

        for (std::vector<std::string> v : clause_in_string) {

            Clause clause;

            for (std::string s : v) {
                bool negated = s.size() == 2 ? true : false;
                int var = negated ? (int)s[1] : (int)s[0];

                if (std::find(clause.literals.begin(), clause.literals.end(), literal(var, negated)) == clause.literals.end())
                    clause.literals.push_back(literal(var, negated));

                if (std::find(variables.begin(), variables.end(), var) == this->variables.end())
                    this->variables.push_back(var);
            }

            bool add_clause = true;
            for (literal l : clause.literals) {
                for (literal k : clause.literals) {
                    if (std::get<0>(l) == std::get<0>(k) && std::get<1>(l) != std::get<1>(k)) {
                        add_clause = false;
                        break;
                    }
                }
            }


            if (add_clause)
                this->clauses.push_back(clause);
        }
    }

    /**
     * Makes a copy from a ClauseSet.
     */
    ClauseSet(const ClauseSet& other) {
        this->variables = std::vector<int>(other.variables);
        this->clauses = std::vector<Clause>(other.clauses);
    }

    /**
     * Checks whether there is an empty clause.
     */
    bool has_empty_clause() {
        for(Clause c : clauses) {
            if(c.literals.empty()) return true;
        }
        return false;
    }

    /**
     * Checks whether there is a clause with one non-negated literal.
     * If it exists, returns a reference to it through the pointer passed.
     */
    bool has_non_negated_unit_clause(literal *var) { 
        for(Clause c : clauses) {
            if(c.size() == 1 && !std::get<1>(c.literals[0])) {
                *var = c.literals[0];
                return true;
            }
        }
        return false;
    }

    /**
     * Self-explanatory
     */
    int count_clauses_containing_var_with_specified_size(int var, int clause_size) { 
        int answer = 0;
        for(Clause c : clauses) {
            if(c.size() == clause_size) {
                for(literal l : c.literals) {
                    if(std::get<0>(l) == var) {
                        answer++;
                        break;
                    }
                } 
            }
        }
        return answer;
     }

    /**
     * Returns the size of the longest clause.
     * The size of the clause is its amount of literals.
     */
    int longest_clause_size() { 
        int maximum_size = 0;
        for(Clause c : clauses) {
            if(c.size() > maximum_size) {
                maximum_size = c.size();
            }
        }
        return maximum_size;
    }

    /**
     * Checks if a variable has non-negated occurences.
     */
    bool has_non_negated_occurences(int var) {
        for (Clause c : clauses) {
            for (literal l : c.literals) {
                bool negated = std::get<1>(l);
                if (std::get<0>(l) == var && !negated)
                    return true;
            }
        }

        return false;
    }

    /**
     * Checks if a variable has more non-negated occurences
     * (weighted sum where occurences in smaller clauses have greater weight).
     */
    bool has_greater_positive_occurences(int var) {

        double n_pos = 0, n_neg = 0;

        for (Clause c : clauses) {
            int size = c.size();
            for (literal l : c.literals) {
                bool negated = std::get<1>(l);
                if (std::get<0>(l) == var) {
                    n_pos += (!negated) * (1.0/size);
                    n_neg += negated * (1.0/size);
                }
            }
        }

        return n_pos > n_neg;
    }

    /**
     * Applies the value to the variable.
     * This method removes all clauses that will be satisfied and removes literals wich will never
     * be satisfied. All in a copy of the clause set that is then returned.
     */
    ClauseSet *apply(int var, bool value) { 
        ClauseSet * new_clause_set = new ClauseSet(*this);

        int sz = new_clause_set->clauses.size();
        int index = 0;
        for(int i=0; i<sz; i++) {
            auto &literals = new_clause_set->clauses[index].literals;
            
            bool is_clause_satisfied = std::find(literals.begin(), literals.end(), literal(var, !value)) != literals.end();
            auto oposite_literal = std::find(literals.begin(), literals.end(), literal(var, value));

            if(is_clause_satisfied) {
                new_clause_set->clauses.erase(new_clause_set->clauses.begin() + index);
            } else {
                if(oposite_literal != literals.end()) literals.erase(oposite_literal);
                index++;
            }
        }

        auto &new_variables = new_clause_set->variables;
        auto var_it = std::find(new_variables.begin(), new_variables.end(), var);
        if (var_it != new_variables.end())
            new_variables.erase(var_it);

        return new_clause_set;
    }

    void print() {
        std::cout << "[";
        for (Clause c : clauses) {
            c.print();
            std::cout << ", ";
        }
        std::cout << "] var(";
        for (int var : variables) {
            std::cout << var << ", ";
        }
        std::cout << ")\n";
    }
};

/**
 * Checks if a solution satisfies a clause set.
 */
bool verifier(ClauseSet * clause_set, std::string solution) {

    std::map<int, bool> var_values;
    
    std::istringstream iss(solution);

    std::string word;

    while (iss >> word) {
        char value = word.back();
        int var = std::stoi(word.substr(0, word.size() - 1));
        var_values[var] = value == 'T';
    }

    bool answer = true;

    for (Clause c : clause_set->clauses) {

        bool clause_answer = false;

        for (literal l : c.literals) {
            if (std::get<1>(l)) {
                clause_answer = clause_answer || !var_values[std::get<0>(l)];
            }
            else {
                clause_answer = clause_answer || var_values[std::get<0>(l)];
            }
        }

        answer = answer && clause_answer;

    }

    return answer;

}

#endif