#include <iostream>
#include <chrono>
#include "DPLL.cpp"
#include "CIDPLL.cpp"
#include "Clause.cpp"
#include "CNF_reader.cpp"

int main(int argc, char **argv)
{

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

        } else {
            std::cout << "Error: please specify an algorithm.\n";
            return 0;
        }

        auto start = std::chrono::high_resolution_clock::now();

        auto dpll_return = alg(test, "");

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start; // time in seconds

        bool value = std::get<0>(dpll_return);
        std::string solution = std::get<1>(dpll_return);

        bool is_satisfiable = verifier(test, solution);
        bool is_correct = false;//std::get<0>(DPLL(test)) == value; this is deactivated due to excessive prolongation of the test results

        outFile << std::get<0>(dpll_return) << ", " << is_satisfiable << ", " << is_correct << ", " << solution << ", " << duration.count();
        std::cout << "Result saved in " << solution_path << '\n';
    }
    else {
        std::cout << "Error: please specify a file.\n";
    }

    return 0;
}