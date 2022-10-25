//
// Created by finnw on 24.10.2022.
//

#include "EightQueens.hpp"
#include <iostream>
#include <random>

int Chessboard::calculateFitness() {
    int collisions = 0;
    for(int i = 0; i < 8; i ++) {
        int column = i;
        int row = this->queens[i];
        for(int j = i; j < 8; j ++) {
            if(i == j) continue;
            if(this->queens[j] == row) { //Same row?
                collisions++;
            }
            if(this->queens[j] == j+(row-i)) { //On diagonal (topLeft->bottomRight)
                collisions++;
            }
            if(this->queens[j] == -j+(row+i)) { //On diagonal (bottomLeft->topRight)
                collisions++;
            }
            //Same column can not occur based on encoding.
        }
    }
    return collisions;
}

bool EightQueens::isGoal(Chessboard* state) {
    int fit = state->calculateFitness();
    //printf("Fitness: %d\n", fit);
    return fit == 0;
}

void EightQueens::display(Chessboard* state) {
    for(int i = 0; i < 8; i ++) {
        std::printf("%s%s%s%s%s%s%s%s\n", (state->queens[i]==0?"Q":"#"), (state->queens[i]==1?"Q":"#"), (state->queens[i]==2?"Q":"#"), (state->queens[i]==3?"Q":"#"), (state->queens[i]==4?"Q":"#"), (state->queens[i]==5?"Q":"#"), (state->queens[i]==6?"Q":"#"), (state->queens[i]==7?"Q":"#"));
    }
}

bool EightQueens::compare(Chessboard &a, Chessboard &b) {
    return a.calculateFitness() < b.calculateFitness();
}

void EightQueens::cross(Chessboard &a, Chessboard &b, Chessboard* out) {
    out->queens[0] = a.queens[0];
    out->queens[0] = a.queens[1];
    out->queens[0] = a.queens[2];
    out->queens[0] = a.queens[3];
    out->queens[0] = b.queens[4];
    out->queens[0] = b.queens[5];
    out->queens[0] = b.queens[6];
    out->queens[0] = b.queens[7];
}

void EightQueens::mutate(Chessboard* instance, float rate) {
    for(int i = 0; i < 8; i ++) {
        float a = randPercent;
        if(a <= rate) {
            instance->queens[i] = this->intDist(this->generator);
        }
    }
}

void EightQueens::generateRandom(Chessboard* board) {
    for(int i = 0; i < 8; i ++)
        board->queens[i] = this->intDist(this->generator);
}



