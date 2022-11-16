//
// Created by finnw on 24.10.2022.
//

#ifndef MEILENSTEIN_1_2_GENETICALGORITHM_HPP
#define MEILENSTEIN_1_2_GENETICALGORITHM_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include "RandomStuff.hpp"
#include "Stundenplan.hpp"

namespace KI {

    namespace GeneticAlgorithm {

        template<typename T>
        class Problem {
            public:
                explicit Problem(float mutationRate, int populationSize, int maxGenerations,
                                 bool (*compareFunction)(T &, T &))
                        : mutationRate{mutationRate}, populationSize{populationSize}, maxGenerations{maxGenerations},
                          compareFunction{compareFunction} {
                }

                ~Problem() {
                    /*std::free(this->states);
                    std::free(this->newStates);
                    this->states = nullptr;
                    this->newStates = nullptr;*/
                };


                std::pair<T, std::pair<int, int>> solve() {
                    this->states = (T *) std::calloc(sizeof(T), this->populationSize);
                    this->newStates = (T *) std::calloc(sizeof(T), this->populationSize);

                    printf("States from: %p to %p\n", this->states, this->states + this->populationSize);
                    printf("NewStates from: %p to %p\n", this->newStates, this->newStates + this->populationSize);
                    std::flush(std::cout);

                    for (int i = 0; i < this->populationSize; i++) {
                        this->generateRandom(&this->states[i]);
                    }

                    std::sort(this->states, this->states + this->populationSize, this->compareFunction);
                    printf("After Sort.\n");
                    std::flush(std::cout);

                    T best = T(this->states[0]);
                    int bestGen = 0;

                    int generation = 0;
                    while (generation < this->maxGenerations && !isGoal(&this->states[0])) {

                        for (int i = 0; i < this->populationSize; i += 2) {
                            T *father = &this->states[0];
                            T *mother = &this->states[getNumberInRange(0, this->populationSize / 4)];
                            this->cross(father, mother, &this->newStates[i]);
                            this->cross(mother, father, &this->newStates[i + 1]);
                            this->mutate(&this->newStates[i], this->mutationRate);
                            this->mutate(&this->newStates[i + 1], this->mutationRate);
                        }

                        std::sort(this->newStates, this->newStates + this->populationSize, this->compareFunction);
                        printf("After Sort.\n");
                        std::flush(std::cout);

                        if (this->compareFunction(this->newStates[0], best)) {
                            best = T(this->newStates[0]);
                            bestGen = generation;
                        }

                        uint64_t fitnessSum = 0;
                        for (int i = 0; i < this->populationSize; i++) {
                            fitnessSum += this->newStates[i].calculateFitness();
                        }
                        //printf("%d;%d;%d;%.0f\n", generation, best.calculateFitness(), this->newStates[0].calculateFitness(), (float) fitnessSum / this->populationSize);

                        //Swapping Buffers
                        T *tmp = this->states;
                        this->states = this->newStates;
                        this->newStates = tmp;

                        generation++;
                    }

                    std::sort(this->states, this->states + this->populationSize, this->compareFunction);
                    printf("After Sort.\n");
                    std::flush(std::cout);

                    if (isGoal(&this->states[0])) {
                        return std::pair<T, std::pair<int, int>>(this->states[0], std::pair<int, int>(generation, best.calculateFitness()));
                    }
                    printf("Best found after %d generations.\n", bestGen);
                    return std::pair<T, std::pair<int, int>>(best, std::pair<int, int>(generation, best.calculateFitness()));
                }

                virtual bool isGoal(T *state) = 0;

                virtual void cross(T *parent1, T *parent2, T *out) = 0;

                virtual void mutate(T *element, float rate) = 0;

                virtual void generateRandom(T *) = 0;

                virtual void display(T *element) = 0;

            private:
                float mutationRate;
                int populationSize;
                int maxGenerations;

                bool (*compareFunction)(T &, T &);

                T *states = nullptr;
                T *newStates = nullptr;

        };

    }

}


#endif //MEILENSTEIN_1_2_GENETICALGORITHM_HPP
