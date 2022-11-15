//
// Created by finnw on 14.11.2022.
//

#include "Stundenplan.hpp"

void StundenplanProblem::generateRandom(Stundenplan *out) {
    //Place Modules in random day in random slot in random room
    for(int i = 0; i < MODULES_TOTAL; i ++) {
        out->modules[i][I_DAY] = getNumberInRange(0, DAYS_IN_WEEK - 1); //Day
        out->modules[i][I_SLOT] = getNumberInRange(0, SLOTS_PER_DAY - 1); //Slot
        out->modules[i][I_ROOM] = getNumberInRange(0, MAX_ROOMS - 1); //Room
    }
}

bool doLecturerOverlay(int modA, int modB) {
    for(int i = 0; i < sizeof(ModuleLecturer) / sizeof(int[2]); i ++) {
        if(ModuleLecturer[i][0] == modA) {
            for(int j = 0; j < sizeof(ModuleLecturer) / sizeof(ModuleLecturer[0]); j ++) {
                if(ModuleLecturer[j][0] == modB && ModuleLecturer[i][1] == ModuleLecturer[j][1]) {
                    return true;
                }
            }
        }
    }
    return false;
}

int Stundenplan::calculateFitness() {

    int collisions_1 = 0; //Collisions between modules in same semester
    int collisions_2 = 0; //Collisions between modules with same lecturer
    int collisions_3 = 0; //Collisions between modules in same room

    for(int i = 0; i < MODULES_TOTAL; i ++) {
        int* modA = modules[i];
        for(int j = i + 1; j < MODULES_TOTAL; j ++) {
            int* modB = modules[j];
            //Same Day & Timeslot
            if(modA[I_DAY] == modB[I_DAY] && modA[I_SLOT] == modB[I_SLOT]) {
                if(ModuleSemester[i] == ModuleSemester[j]) { //Same Semester
                    collisions_1 ++;
                }
                if(doLecturerOverlay(i, j)) { //Same Lecturer
                    collisions_2 ++;
                }
                if(modA[I_ROOM] == modB[I_ROOM]) { //Same Room
                    collisions_3 ++;
                }
            }
        }
    }

    return 100*collisions_1 + 100*collisions_2 + 100*collisions_3;
}

void StundenplanProblem::cross(Stundenplan *a, Stundenplan *b, Stundenplan *out) {
    for(int i = 0; i < MODULES_TOTAL; i ++) {
        out->modules[i][0] = getRandomBool() ? a->modules[i][0] : b->modules[i][0]; //Random Day from A or B
        out->modules[i][1] = getRandomBool() ? a->modules[i][1] : b->modules[i][1]; //Random Slot from A or B
        out->modules[i][2] = getRandomBool() ? a->modules[i][2] : b->modules[i][2]; //Random Room from A or B
    }
}

void StundenplanProblem::mutate(Stundenplan *instance, float rate) {
    for(int i = 0; i < MODULES_TOTAL; i ++) {
        if(getRandomFloat() < rate) {
            instance->modules[i][0] = getNumberInRange(0, DAYS_IN_WEEK - 1); //Day
        }
        if(getRandomFloat() < rate) {
            instance->modules[i][1] = getNumberInRange(0, SLOTS_PER_DAY - 1); //Slot
        }
        if(getRandomFloat() < rate) {
            instance->modules[i][2] = getNumberInRange(0, MAX_ROOMS - 1); //Room
        }
    }
}

bool StundenplanProblem::isGoal(Stundenplan *state) {
    //Function will never find the perfect solution, so it will always return false.
    //Maybe it will find a near perfect solution.
    return state->calculateFitness() == 0;
}

bool StundenplanProblem::compare(Stundenplan &a, Stundenplan &b) {
    return a.calculateFitness() < b.calculateFitness();
}

void StundenplanProblem::display(Stundenplan *state) {

    for(int i = 0; i < DAYS_IN_WEEK; i ++) {
        printf("%s:\n", Workdays[i]);
        for(int j = 0; j < SLOTS_PER_DAY; j ++) {
            printf("Slot %d (%02d-%02d): ", j, 8 + j*2, 8+(j+1)*2);
            for(int k = 0; k < MODULES_TOTAL; k ++) {
                if(state->modules[k][I_DAY] == i && state->modules[k][I_SLOT] == j) {
                    printf("%s (Room %02d), ", Modules[k], state->modules[k][I_ROOM]);
                }
            }
            printf("\n");
        }
    }
}
