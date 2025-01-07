#include <iostream>
#include <chrono>
#include "DPLL.cpp"
#include "CIDPLL.cpp"
#include "TS.cpp"
#include "Clause.cpp"
#include "CNF_reader.cpp"

int main(int argc, char **argv)
{
    srand(time(0));
    
    //ClauseSet *test = new ClauseSet({{"x", "-y"}, {"x"}, {"y"}});
    //ClauseSet *test = new ClauseSet((StringClause){{"-x"}, {"x"}});

    //std::cout << DPLL(test) << '\n';

    /**
    * Running the tests for the specified file path in argv.
    */
    if (argc > 1) {
        std::string input_algorithm = argv[1];
        auto input_filepath = argv[2];

        std::cout << "Executing tests for: " << input_filepath << '\n';
        ClauseSet *test = CNF_reader(input_filepath);

        std::string solution_path = std::string(input_filepath) + "_" + input_algorithm + "_results.txt";
        std::ofstream outFile(solution_path);

        sat_solution(*alg)(ClauseSet *, std::string);

        if (input_algorithm == "DPLL") {

            alg = DPLL;

        } else if (input_algorithm == "CIDPLL") {

            alg = CIDPLL;

        } else if (input_algorithm == "TS") {

            alg = TS;

        } else {
            std::cout << "Error: please specify an algorithm.\n";
            return 0;
        }

        auto start = std::chrono::high_resolution_clock::now();

        auto alg_return = alg(test, "");

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start; // time in seconds

        bool value = std::get<0>(alg_return);
        std::string solution = std::get<1>(alg_return);

        //bool is_satisfiable = verifier(test, solution);
        int quality = evaluator(test, solution);

        std::string execution_info = std::to_string(std::get<0>(alg_return)) + ", " + std::to_string(quality) +
         ", " + solution + ", " + std::to_string(duration.count());

        outFile << execution_info;
        std::cout << "Result for " << input_filepath << ": " << execution_info << "\n";
        std::cout << "Result saved in " << solution_path << '\n';
    }
    else {
        std::cout << "Error: please specify a file.\n";
    }

    return 0;
}