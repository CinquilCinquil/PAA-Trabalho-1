#ifndef Clauses
#define Clauses

#include <tuple>
#include <vector>
#include <algorithm>
#include <string>

using literal = std::tuple<int, bool>;
using StringClause = std::vector<std::vector<std::string>>;

class Clause
{
public:
    std::vector<literal> literals;

    std::vector<int> get_variables();
};

class ClauseSet
{
public:
    std::vector<int> variables;
    std::vector<Clause> clauses;

    ClauseSet(StringClause clause_in_string) {

        for (std::vector<std::string> v : clause_in_string) {

            Clause clause;

            for (std::string s : v) {
                int var = (int)s[0];
                int negated = s.size() == 1 ? true : false;

                clause.literals.push_back(literal(var, negated));

                if (std::find(variables.begin(), variables.end(), var) != this->variables.end())
                    this->variables.push_back(var);
            }

            this->clauses.push_back(clause);
        }
    }

    bool has_empty_clause() { return false; }

    bool has_unit_clause(int *var) { return false; }

    int clauses_with_var(int var, int clause_size) { return 0; }

    int longest_clause_size() { return 0; }

    ClauseSet *apply(int var, bool value) { return NULL; }
};

#endif