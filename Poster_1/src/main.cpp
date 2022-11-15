#include "Stundenplan.hpp"

//#define PRINT_CSV


int main() {

    StundenplanProblem problem = StundenplanProblem(0.2f, 10, 1000);
    auto ret = problem.solve();

    problem.display(ret.first);

    return 0;
}
