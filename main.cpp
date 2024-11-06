#include <iostream>
#include <chrono>
#include "DPLL.cpp"
#include "Clause.cpp"
#include "CNF_reader.cpp"

int main(int argc, char **argv)
{

    //ClauseSet *test = new ClauseSet({{"x", "-y"}, {"x"}, {"y"}});
    //ClauseSet *test = new ClauseSet((StringClause){{"-x"}, {"x"}});

    //std::cout << DPLL(test) << '\n';

    if (argc > 1) {
        std::cout << "Executing tests for: " << argv[1] << '\n';
        ClauseSet *test = CNF_reader(argv[1]);

        std::string solution_path = std::string(argv[1]) + "_results.txt";
        std::ofstream outFile(solution_path);

        auto start = std::chrono::high_resolution_clock::now();

        auto dpll_return = DPLL(test);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start; // time in seconds

        outFile << std::get<0>(dpll_return) << ", " << std::get<1>(dpll_return) << ", " << duration.count();
        std::cout << "Result saved in " << solution_path << '\n';
    }
    else {
        std::cout << "Error: please specify a file.\n";
    }

    return 0;
}