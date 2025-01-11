#include <iostream>
#include <chrono>
#include <stdlib.h>
#include "DPLL.cpp"
#include "CIDPLL.cpp"
#include "TS.cpp"
#include "Clause.cpp"
#include "CNF_reader.cpp"
#include "GENETIC.cpp"

int main(int argc, char **argv)
{   
    //ClauseSet *test = new ClauseSet({{"x", "-y"}, {"x"}, {"y"}});
    //ClauseSet *test = new ClauseSet((StringClause){{"-x"}, {"x"}});

    //std::cout << DPLL(test) << '\n';

    /**
    * Running the tests for the specified file path in argv.
    */
    if (argc >= 4) {
        std::string input_algorithm = argv[1];
        auto input_filepath = argv[2];
        int repetitions = std::stoi(argv[3]);

        if (repetitions <= 0) {
            std::cout << "Error: 'repetitions' must be a positive number.\n";
            return 0;
        }

        unsigned int seed;
        if(argc == 5) {
            seed = std::stoi(argv[4]);
        } else {
            seed = time(0);
        }

        sat_solution(*alg)(ClauseSet *, std::string);

        if (input_algorithm == "DPLL") {

            alg = DPLL;

        } else if (input_algorithm == "CIDPLL") {

            alg = CIDPLL;

        } else if (input_algorithm == "TS") {

            alg = TS;

        } else if (input_algorithm == "GENETIC") {

            alg = GENETIC;

        } else {
            std::cout << "Error: please specify a valid algorithm.\n";
            return 0;
        }

        std::cout << "Executing tests for: " << input_filepath << '\n';
        ClauseSet *test = CNF_reader(input_filepath);

        std::string solution_path = std::string(input_filepath) + "_" + input_algorithm + "_results.txt";
        std::ofstream outFile(solution_path);

        std::string total_execution_info;
    
        for (int i = 0;i < repetitions;i ++) {

            srand(seed+i);
            if (input_algorithm == "TS") {
                set_seed_TS(seed+i);
            } else if (input_algorithm == "GENETIC") {
                set_seed_GENETIC(seed+i);
            }

            auto start = std::chrono::high_resolution_clock::now();

            auto alg_return = alg(test, "");

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start; // time in seconds

            bool value = std::get<0>(alg_return);
            std::string solution = std::get<1>(alg_return);

            //bool is_satisfiable = verifier(test, solution);
            int quality = evaluator(test, solution);

            std::string execution_info = std::to_string(std::get<0>(alg_return)) +
            ", " + std::to_string(quality) +
            ", " + solution +
            ", " + std::to_string(duration.count()) +
            ", " + std::to_string(seed + i) + '\n';

            total_execution_info += execution_info;
            outFile << execution_info;
        }

        std::cout << "Result for " << input_filepath << ":\n" << total_execution_info;
        std::cout << "Result saved in " << solution_path << '\n';
    }
    else {
        std::cout << "Error: Invalid command. Please check README.md .\n";
    }

    return 0;
}