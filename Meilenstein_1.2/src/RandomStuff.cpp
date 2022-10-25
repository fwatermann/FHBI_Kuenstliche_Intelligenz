//
// Created by finnw on 25.10.2022.
//
#include "RandomStuff.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());

int getNumberInRange(int start, int end) {
    std::uniform_int_distribution<> dis(start, end);
    return dis(gen);
}

float getRandomPercent() {
    std::uniform_real_distribution<> dis(0.0f, 1.0f);
    return (float)dis(gen);
}

bool getRandomBool() {
    std::bernoulli_distribution dis;
    return dis(gen);
}