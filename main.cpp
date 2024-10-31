#include <iostream>
#include "DPLL.cpp"
#include "Clause.cpp"

int main() {

    ClauseSet * test = new ClauseSet({
        {"x", "-y"}, {"x"}, {"y"}
    });

    // std::cout << DPLL(test) << '\n';

    return 0;
}