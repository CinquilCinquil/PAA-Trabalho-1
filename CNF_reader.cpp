#ifndef CNF_reader
#define CNF_reader_file

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Clause.cpp"

ClauseSet* CNF_reader(char * filename) {
    
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return NULL;
    }

    ClauseSet * clause_set  = new ClauseSet();
    int n_variables = 0;

    std::string line;
    bool start_reading_clauses = false;
    while (std::getline(file, line)) {

        if (line[0] == '%') {
            break;
        }

        if (start_reading_clauses) {
            std::istringstream lineStream(line);

            Clause clause;

            int number;
            while (lineStream >> number) {
                if (number == 0)
                    break;
                
                clause.literals.push_back(literal(abs(number), number < 0));
                n_variables = std::max(abs(number), n_variables);
            }

            clause_set->clauses.push_back(clause);

        } else  {
            if (line[0] == 'p')
                start_reading_clauses = true;
        }
    }

    for (int i = 1;i <= n_variables;i ++) {
        clause_set->variables.push_back(i);
    }

    file.close();

    return clause_set;

}


#endif