#include <iostream>
#include <chrono>
#include <stdlib.h>
#include "./algorithms/DPLL.cpp"
#include "./algorithms/CIDPLL.cpp"
#include "./algorithms/TS.cpp"
#include "Clause.cpp"
#include "CNF_reader.cpp"
#include "./algorithms/GENETIC.cpp"

#ifdef __unix__

#define JOIN "/"

#elif defined(_WIN32) || defined(WIN32)

#define JOIN "\\"

#endif


enum ARGUMENTS {
    PROGRAM_NAME,
    ALGORITHM_ARG,
    INPUT_FILE_ARG,
    OUTPUT_FOLDER_ARG,
    REPETITIONS_ARG,
    SEED_ARG
};

std::string get_file_name(char *filepath) {
    std::string path = std::string(filepath);
    std::string name_with_extension = path.substr(path.find_last_of("/\\")+1);
    int last_point = name_with_extension.find_last_of('.');
    std::string name_without_extension = name_with_extension.substr(0, last_point);
    return name_without_extension;
}
int main(int argc, char **argv)
{   
    //ClauseSet *test = new ClauseSet({{"x", "-y"}, {"x"}, {"y"}});
    //ClauseSet *test = new ClauseSet((StringClause){{"-x"}, {"x"}});

    //std::cout << DPLL(test) << '\n';

    /**
    * Running the tests for the specified file path in argv.
    */
    if (argc >= 5) {
        std::string input_algorithm = argv[ALGORITHM_ARG];
        auto input_filepath = argv[INPUT_FILE_ARG];
        auto output_folderpath = argv[OUTPUT_FOLDER_ARG];
        int repetitions = std::stoi(argv[REPETITIONS_ARG]);

        if (repetitions <= 0) {
            std::cout << "Error: 'repetitions' must be a positive number.\n";
            return 0;
        }

        unsigned int seed;
        if(argc == SEED_ARG+1) {
            seed = std::stoi(argv[SEED_ARG]);
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
        
        std::string input_filename = get_file_name(input_filepath);
        std::string solution_path = std::string(output_folderpath) + JOIN + input_filename + "_" + input_algorithm + "_results.txt";
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