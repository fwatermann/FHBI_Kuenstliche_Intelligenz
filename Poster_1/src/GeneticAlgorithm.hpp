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
#define randOut(min, max) (min + ( std::rand() % ( max - min + 1 ) ))
#define randPercent (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX))

namespace KI {

    namespace GeneticAlgorithm {

        template<typename T>
        class Problem {
            public:
                explicit Problem(float mutationRate, int populationSize, int maxGenerations, bool (*compareFunction)(T&, T&))
                        : mutationRate{mutationRate}, populationSize{populationSize}, maxGenerations{maxGenerations}, compareFunction{compareFunction} {
                }

                ~Problem() {
                    /*std::free(this->states);
                    std::free(this->newStates);
                    this->states = nullptr;
                    this->newStates = nullptr;*/
                };


                std::pair<T*, std::pair<int ,int>> solve() {
                    //printf("PopulationSize: %d MutationRate: %f MaxGenerations: %d\n", this->populationSize, this->mutationRate, this->maxGenerations);
                    this->states = (T*) std::calloc(sizeof(T) * this->populationSize, 1);
                    this->newStates = (T*) std::calloc(sizeof(T) * this->populationSize, 1);

                    //printf("Ptr: 0x%p Size: %d\n", this->states, sizeof(T) * this->populationSize);

                    for(int i = 0; i < this->populationSize; i ++) {
                        this->generateRandom(&this->states[i]);
                    }
                    std::sort(this->states, &this->states[this->populationSize], this->compareFunction);

                    int generation = 0;
                    while(generation < this->maxGenerations && !isGoal(&this->states[0])) {

                        //this->newStates = (T*) std::malloc(sizeof(T) * this->populationSize);
                        //std::sort(this->states, &this->states[this->populationSize], this->compareFunction);

                        for(int i = 0; i < this->populationSize; i+=2) {
                            T* father = &this->states[0];
                            T* mother = &this->states[getNumberInRange(0, this->populationSize / 4)];
                            this->cross(father, mother, &this->newStates[i]);
                            this->cross(mother, father, &this->newStates[i+1]);
                            this->mutate(&this->newStates[i], this->mutationRate);
                            this->mutate(&this->newStates[i+1], this->mutationRate);
                        }

                        std::sort(this->newStates, &this->newStates[this->populationSize], this->compareFunction);

                        //Swapping Buffers
                        T* tmp = this->states;
                        this->states = this->newStates;
                        this->newStates = tmp;

                        //printf("Generation: %d\n", generation);
                        //printf("[%d, %d, %d, %d, %d, %d, %d, %d]\n", this->states[0].queens[0], this->states[0].queens[1], this->states[0].queens[2], this->states[0].queens[3], this->states[0].queens[4], this->states[0].queens[5], this->states[0].queens[6], this->states[0].queens[7]);

                        generation ++;
                    }

                    std::sort(this->states, &this->states[this->populationSize], this->compareFunction);

                    if(isGoal(&this->states[0])) {
                        return std::pair<T*, std::pair<int, int>>(&this->states[0], std::pair<int, int>(generation, this->states[0].calculateFitness()));
                    }
                    return std::pair<T*, std::pair<int, int>>(nullptr, std::pair<int, int>(generation, this->states[0].calculateFitness()));
                }

                virtual bool isGoal(T* state) = 0;

                virtual void cross(T* parent1, T* parent2, T* out) = 0;

                virtual void mutate(T* element, float rate) = 0;

                virtual void generateRandom(T*) = 0;

            private:
                float mutationRate;
                int populationSize;
                int maxGenerations;

                /*std::mt19937 generator = std::mt19937();
                std::uniform_int_distribution<int> popDist = std::uniform_int_distribution<int>(0, this->populationSize);
                std::uniform_int_distribution<int> top25Dist = std::uniform_int_distribution<int>(0, (int)(0.25 * this->populationSize));
                std::uniform_real_distribution<float> floatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);*/

                bool (*compareFunction)(T&, T&);

                T* states = nullptr;
                T* newStates = nullptr;

        };

    }

}


#endif //MEILENSTEIN_1_2_GENETICALGORITHM_HPP
