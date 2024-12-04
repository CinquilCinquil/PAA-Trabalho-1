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
        std::cout << "Executing tests for: " << argv[1] << '\n';
        ClauseSet *test = CNF_reader(argv[1]);

        std::string solution_path = std::string(argv[1]) + "_results.txt";
        std::ofstream outFile(solution_path);

        auto start = std::chrono::high_resolution_clock::now();

        auto dpll_return = DPLL(test);

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