//
// Created by finnw on 25.10.2022.
//

#include "KartenFaerben.hpp"
#include "RandomStuff.hpp"

std::vector<std::vector<int>> KartenFaerben::edges = {{1, 2}, {2, 3}, {3}, {4}, {}, {}};

bool KartenFaerben::isGoal(Karte *state) {
    return state->calculateFitness() <= 3;
}

void KartenFaerben::display(Karte *state) {
    printf("%d %d %d %d %d %d", state->colors[0], state->colors[1], state->colors[2], state->colors[3], state->colors[4], state->colors[5]);
}

void KartenFaerben::cross(Karte *a, Karte *b, Karte *out) {
    for(int i = 0; i < 6; i ++) {
        out->colors[i] = getRandomBool() ? a->colors[i] : b->colors[i];
    }
}

void KartenFaerben::mutate(Karte *instance, float rate) {
    for(int i = 0; i < 6; i ++) {
        float a = getRandomPercent();
        if(a <= rate) {
            instance->colors[i] = getNumberInRange(0, 5);
        }
    }
}

void KartenFaerben::generateRandom(Karte *out) {
    for(int i = 0; i < 6; i ++){
        out->colors[i] = getNumberInRange(0, 5);
    }
}

int Karte::calculateFitness() {
    int conflicts = 0;
    int colorCount = 0;
    uint8_t hasColor = 0b00000000;

    for(int i = 0; i < KartenFaerben::edges.size(); i ++) {
        std::vector<int> neightbours = KartenFaerben::edges[i];
        for(int j = 0; j < neightbours.size(); j ++) {
            if(this->colors[neightbours[j]] == this->colors[i]) {
                conflicts ++;
            }
        }
    }

    for(int i = 0; i < 6; i ++) {
        if(!(hasColor & (1 << this->colors[i]))) {
            hasColor |= (1 << this->colors[i]);
            colorCount ++;
        }
    }
    return colorCount + 4*conflicts;
}

bool KartenFaerben::compare(Karte &a, Karte &b) {
    return a.calculateFitness() < b.calculateFitness();
}