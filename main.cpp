#include <iostream>
#include "DPLL.cpp"
#include "Clause.cpp"
#include "CNF_reader.cpp"

int main(int argc, char **argv)
{

    //ClauseSet *test = new ClauseSet({{"x", "-y"}, {"x"}, {"y"}});
    //ClauseSet *test = new ClauseSet((StringClause){{"-x"}, {"x"}});

    //std::cout << DPLL(test) << '\n';

    if (argc > 0) {
        std::cout << "Executando testes para: " << argv[1] << '\n';
        ClauseSet *test = CNF_reader(argv[1]);
        test->print();

        std::cout << DPLL(test) << '\n';
    }

    return 0;
}