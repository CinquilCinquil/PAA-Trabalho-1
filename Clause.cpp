#ifndef CLAUSE
#define CLAUSE

#include <tuple>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <sstream>

using literal = std::tuple<int, bool>; /*<variable id, negated> */
using StringClause = std::vector<std::vector<std::string>>;

class Clause {
public:
    std::vector<literal> literals;

    std::vector<int> get_variables();

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
     * Constrói o conjunto de cláusulas a partir de várias strings.
     * {{"x"}, {"-x", "y"}, {"-y"}} representa a expressão
     * (x) E (NÃO x OU y) E (NÃO y)
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
     * Constrói uma cópia de um conjunto de cláusulas.
     */
    ClauseSet(const ClauseSet& other) {
        this->variables = std::vector<int>(other.variables);
        this->clauses = std::vector<Clause>(other.clauses);
    }

    /**
     * Checa se existe alguma cláusula vazia
     */
    bool has_empty_clause() {
        for(Clause c : clauses) {
            if(c.literals.empty()) return true;
        }
        return false;
    }

    /**
     * Checa se existe alguma cláusula com apenas 1 literal não negado.
     * Se existir, retorna a referência para o literal pelo ponteiro passado.
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
     * Auto-explicativo
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
     * Retorna o tamanho da cláusula mais longa.
     * O tamanho de uma cláusula é a sua quantidade de literais.
     */
    int longest_clause_size() { 
        int maximum_size = 0;
        for(Clause c : clauses) {
            if(c.size() > maximum_size) {
                maximum_size = c.literals.size();
            }
        }
        return maximum_size;
    }

    /**
     * Checa se uma variável tem ocorrências não negadas.
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
     * Checa se uma variável tem mais ocorrências não negadas
     * (soma ponderada em que aparições em cláusulas menores tem um maior peso).
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
     * Aplica o valor à variável.
     * Esse método remove todas as cláusulas que serão satisfeitas e remove os literais que nunca
     * serão satisfeitos, gerando uma cópia do conjunto de cláusulas.
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
 * Checa se uma solução está satisfaz um conjunto de cláusulas.
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