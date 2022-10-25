//
// Created by finnw on 24.10.2022.
//

#ifndef MEILENSTEIN_1_2_EIGHTQUEENS_HPP
#define MEILENSTEIN_1_2_EIGHTQUEENS_HPP

#include "GeneticAlgorithm.hpp"
#include <random>

struct Chessboard {
    int calculateFitness();

    int queens[8];
};

class EightQueens : public KI::GeneticAlgorithm::Problem<Chessboard> {
    public:
        EightQueens(float mutationRate, int populationSize, int maxGenerations)
                : KI::GeneticAlgorithm::Problem<Chessboard>(mutationRate, populationSize, maxGenerations, compare) {}

        bool isGoal(Chessboard *state) override;

        void display(Chessboard *state) override;

        void cross(Chessboard* a, Chessboard* b, Chessboard *out) override;

        void mutate(Chessboard *instance, float rate) override;

        void generateRandom(Chessboard *) override;

        static bool compare(Chessboard &a, Chessboard &b);

    private:
        std::default_random_engine generator;
        std::uniform_int_distribution<int> intDist = std::uniform_int_distribution<int>(0, 7);
        std::uniform_int_distribution<int> mutDist = std::uniform_int_distribution<int>(-2, 2);
        std::uniform_real_distribution<float> perDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
        std::bernoulli_distribution boolDist = std::bernoulli_distribution();

};


#endif //MEILENSTEIN_1_2_EIGHTQUEENS_HPP
