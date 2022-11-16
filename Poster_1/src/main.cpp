#include <fstream>
#include <cstring>
#include <algorithm>
#include "Stundenplan.hpp"
#include "RandomStuff.hpp"

std::pair<Stundenplan, int> solve(float mutRate, int popSize, int maxGens, const char* fileoutput = nullptr);

int main() {
    std::pair<Stundenplan, int> result = solve(0.05f, 10, 250);
    printf("Generation: %d, Fitness: %d\n", result.second, StundenplanProblem::calcFitness(&result.first));
    StundenplanProblem::display(&result.first);

    return 0;
}

std::pair<Stundenplan, int> solve(float mutRate, int popSize, int maxGens, const char* fileoutput) {

    /* SETUP */
    Stundenplan *bufferA = (Stundenplan *) std::calloc(popSize, sizeof(Stundenplan));
    Stundenplan *bufferB = (Stundenplan *) std::calloc(popSize, sizeof(Stundenplan));
    //Clear Buffers (to 0)
    std::memset(bufferA, 0, sizeof(Stundenplan) * popSize);
    std::memset(bufferB, 0, sizeof(Stundenplan) * popSize);

    std::sort(bufferA, bufferA + popSize, StundenplanProblem::compare);

    /* ALGORITHM */

    Stundenplan best = Stundenplan(bufferA[0]);
    int bestGen = 0;

    int generation = 0;
    while(generation < maxGens) {

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

        uint64_t fitnessSum = 0;
        for(int i = 0; i < popSize; i++) {
            fitnessSum += StundenplanProblem::calcFitness(&bufferB[i]);
        }
        if(fileoutput != nullptr) {
            std::ofstream out;
            out.open(fileoutput, std::ios::app);
            out << generation << ";" << bestGen << ";" << StundenplanProblem::calcFitness(&best) << ";" << StundenplanProblem::calcFitness(&bufferB[0]) << ";" << (float) fitnessSum / popSize << std::endl;
            out.close();
        } else {
            printf("%d;%d;%d;%.0f\n", generation, StundenplanProblem::calcFitness(&best), StundenplanProblem::calcFitness(&bufferB[0]), (float) fitnessSum / popSize);
        }

        std::swap(bufferA, bufferB);
        generation++;
    }

    return std::pair<Stundenplan, int>(Stundenplan(best), int(bestGen));
}
