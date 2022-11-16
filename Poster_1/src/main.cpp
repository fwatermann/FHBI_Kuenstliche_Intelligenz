#include "Stundenplan.hpp"
//#define PRINT_CSV

std::pair<Stundenplan, int> solve(float mutRate, int popSize, int maxGens);

int main() {
    std::pair<Stundenplan, int> result = solve(0.05f, 100, 250);
    printf("Generation: %d, Fitness: %d\n", result.second, StundenplanProblem::calcFitness(&result.first));
    StundenplanProblem::display(&result.first);

    return 0;
}

std::pair<Stundenplan, int> solve(float mutRate, int popSize, int maxGens) {

    /* SETUP */
    Stundenplan *bufferA = (Stundenplan *) std::calloc(popSize, sizeof(Stundenplan));
    Stundenplan *bufferB = (Stundenplan *) std::calloc(popSize, sizeof(Stundenplan));
    //Clear Buffers (to 0)
    std::memset(bufferA, 0, sizeof(Stundenplan) * popSize);
    std::memset(bufferB, 0, sizeof(Stundenplan) * popSize);

    for(int i = 0; i < popSize; i++) {
        StundenplanProblem::generateRandom(&bufferA[i]);
    }
    std::sort(bufferA, bufferA + popSize, StundenplanProblem::compare);

    /* ALGORITHM */

    Stundenplan best = Stundenplan(bufferA[0]);
    int bestGen = 0;

    int generation = 0;
    while(generation < maxGens && !StundenplanProblem::isGoal(&bufferA[0])) {

        for(int i = 0; i < popSize; i += 2) {
            Stundenplan *father = &bufferA[0];
            Stundenplan *mother = &bufferA[getNumberInRange(0, popSize / 4)];
            StundenplanProblem::cross(father, mother, &bufferB[i]);
            StundenplanProblem::cross(mother, father, &bufferB[i + 1]);
            StundenplanProblem::mutate(&bufferB[i], mutRate);
            StundenplanProblem::mutate(&bufferB[i + 1], mutRate);
        }

        std::sort(bufferB, bufferB + popSize, StundenplanProblem::compare);

        if(StundenplanProblem::compare(bufferB[0], best)) {
            best = Stundenplan(bufferB[0]);
            bestGen = generation;
        }

        std::swap(bufferA, bufferB);
        generation++;
    }

    return std::pair<Stundenplan, int>(Stundenplan(best), int(bestGen));
}
