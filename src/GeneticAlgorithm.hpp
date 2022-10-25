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
#include <random>
#define randOut(min, max) (min + ( std::rand() % ( max - min + 1 ) ))
#define randPercent (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX))

namespace KI {

    namespace GeneticAlgorithm {

        class Individuum {
            public:
                virtual int calculateFitness() = 0;
        };

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


                std::pair<T*, int> solve() {
                    //printf("PopulationSize: %d MutationRate: %f MaxGenerations: %d\n", this->populationSize, this->mutationRate, this->maxGenerations);
                    this->states = (T*) std::malloc(sizeof(T) * this->populationSize);
                    this->newStates = (T*) std::malloc(sizeof(T) * this->populationSize);

                    //printf("Ptr: 0x%p Size: %d\n", this->states, sizeof(T) * this->populationSize);

                    for(int i = 0; i < this->populationSize; i ++) {
                        this->generateRandom(&this->states[i]);
                    }
                    std::sort(this->states, &this->states[this->populationSize], this->compareFunction);

                    int generation = 0;
                    while(generation < this->maxGenerations && !isGoal(&this->states[0])) {

                        //this->newStates = (T*) std::malloc(sizeof(T) * this->populationSize);

                        for(int i = 0; i < this->populationSize; i+=2) {
                            T father = this->states[0];
                            T mother = this->selection();
                            this->cross(father, mother, &this->newStates[i]);
                            this->cross(mother, father, &this->newStates[i+1]);
                            this->mutate(&this->newStates[i], this->mutationRate);
                            this->mutate(&this->newStates[i+1], this->mutationRate);
                        }

                        //Swapping Buffers
                        T* tmp = this->states;
                        this->states = this->newStates;
                        this->newStates = tmp;

                        //printf("Generation: %d\n", generation);
                        //printf("[%d, %d, %d, %d, %d, %d, %d, %d]\n", this->states[0].queens[0], this->states[0].queens[1], this->states[0].queens[2], this->states[0].queens[3], this->states[0].queens[4], this->states[0].queens[5], this->states[0].queens[6], this->states[0].queens[7]);

                        generation ++;
                    }

                    if(isGoal(&this->states[0])) {
                        return std::pair<T*, int>(&this->states[0], generation);
                    }
                    return std::pair<T*, int>(nullptr, generation);
                }

                virtual bool isGoal(T* state) = 0;

                virtual void display(T* state) = 0;

                virtual void cross(T &parent1, T &parent2, T* out) = 0;

                virtual void mutate(T* element, float rate) = 0;

                virtual void generateRandom(T*) = 0;

            private:
                float mutationRate;
                int populationSize;
                int maxGenerations;

                std::default_random_engine generator = std::default_random_engine();
                std::uniform_int_distribution<int> intDist = std::uniform_int_distribution<int>(0, this->populationSize);
                std::uniform_int_distribution<int> top25Dist = std::uniform_int_distribution<int>(0, (int)(0.25*this->populationSize));
                std::uniform_real_distribution<float> floatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);

                bool (*compareFunction)(T&, T&);

                T* states = nullptr;
                T* newStates = nullptr;

                T selection() {
                    std::sort(this->states, &this->states[this->populationSize], this->compareFunction);
                    return this->states[top25Dist(generator)];
                }

                T randomSelection() {
                    std::sort(this->states, &this->states[this->populationSize], this->compareFunction);
                    return this->states[intDist(generator)];
                }

        };

    }

}


#endif //MEILENSTEIN_1_2_GENETICALGORITHM_HPP
