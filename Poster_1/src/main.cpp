#include "Stundenplan.hpp"

//#define PRINT_CSV


int main() {

    StundenplanProblem problem = StundenplanProblem(0.05f, 100, 10000);
    auto ret = problem.solve();
    printf("Fitness: %d\n\n", ret.second.second);
    problem.display(ret.first);

    return 0;
}
