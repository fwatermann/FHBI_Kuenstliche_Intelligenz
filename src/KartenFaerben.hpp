//
// Created by finnw on 25.10.2022.
//

#ifndef MEILENSTEIN_1_2_KARTENFAERBEN_HPP
#define MEILENSTEIN_1_2_KARTENFAERBEN_HPP

#include "GeneticAlgorithm.hpp"

struct Karte {
    int calculateFitness();
    int colors[6];
};

class KartenFaerben : public KI::GeneticAlgorithm::Problem<Karte> {

    public:
        KartenFaerben(float mutatRate, int popSize, int maxGens)
            : KI::GeneticAlgorithm::Problem<Karte>(mutatRate, popSize, maxGens, compare) {}

        bool isGoal(Karte *state) override;
        void display(Karte *state) override;
        void cross(Karte* a, Karte* b, Karte* out) override;
        void mutate(Karte* instance, float rate) override;
        void generateRandom(Karte* out) override;

        static bool compare(Karte &a, Karte &b);
        static std::vector<std::vector<int>> edges;

    private:
        std::default_random_engine generator;
        std::uniform_int_distribution<int> intDist = std::uniform_int_distribution<int>(0, 5);
        std::uniform_int_distribution<int> mutDist = std::uniform_int_distribution<int>(-2, 2);
        std::uniform_real_distribution<float> perDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
        std::bernoulli_distribution boolDist = std::bernoulli_distribution();


};


#endif //MEILENSTEIN_1_2_KARTENFAERBEN_HPP
