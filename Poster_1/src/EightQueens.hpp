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


        void cross(Chessboard* a, Chessboard* b, Chessboard *out) override;

        void mutate(Chessboard *instance, float rate) override;

        void generateRandom(Chessboard *) override;

        static bool compare(Chessboard &a, Chessboard &b);
        static void display(Chessboard *state);

    private:

};


#endif //MEILENSTEIN_1_2_EIGHTQUEENS_HPP
