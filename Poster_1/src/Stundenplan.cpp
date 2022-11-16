//
// Created by finnw on 14.11.2022.
//

#include "Stundenplan.hpp"

void StundenplanProblem::generateRandom(Stundenplan *out) {
    //Place Modules in random day in random slot in random room
    for (int i = 0; i < TOTAL_MODULES; i++) {
        out->modules[i][I_DAY] = getNumberInRange(0, DAYS_IN_WEEK - 1); //Day
        out->modules[i][I_SLOT] = getNumberInRange(0, SLOTS_PER_DAY - 1); //Slot
        out->modules[i][I_ROOM] = getNumberInRange(0, MAX_ROOMS - 1); //Room
    }
}

bool doLecturerOverlap(int modA, int modB) {
    for (int i = 0; i < sizeof(ModuleLecturer) / sizeof(int[2]); i++) {
        if (ModuleLecturer[i][0] == modA) {
            for (int j = 0; j < sizeof(ModuleLecturer) / sizeof(ModuleLecturer[0]); j++) {
                if (ModuleLecturer[j][0] == modB && ModuleLecturer[i][1] == ModuleLecturer[j][1]) {
                    return true;
                }
            }
        }
    }
    return false;
}

char *getLecturerName(int mod) {
    for (int i = 0; i < sizeof(ModuleLecturer) / sizeof(int[2]); i++) {
        if (ModuleLecturer[i][0] == mod) {
            return (char *) Lecturers[ModuleLecturer[i][1]];
        }
    }
    return nullptr;
}

int StundenplanProblem::calcFitness(Stundenplan* state) {
    int collisions_1 = 0; //Collisions between modules in same semester
    int collisions_2 = 0; //Collisions between modules with same lecturer
    int collisions_3 = 0; //Collisions between modules in same room

    for (int i = 0; i < TOTAL_MODULES; i++) {
        for (int j = i + 1; j < TOTAL_MODULES; j++) {
            //Same Day & Timeslot
            if (state->modules[i][I_DAY] == state->modules[j][I_DAY] && state->modules[i][I_SLOT] == state->modules[j][I_SLOT]) {
                if (ModuleSemester[i] == ModuleSemester[j]) { //Same Semester
                    collisions_1++;
                }
                if (doLecturerOverlap(i, j)) { //Same Lecturer
                    collisions_2++;
                }
                if (state->modules[i][I_ROOM] == state->modules[j][I_ROOM]) { //Same Room
                    collisions_3++;
                }
            }
        }
    }

    int badTimedModules = 0;
    for (int i = 0; i < TOTAL_MODULES; i++) {
        if (state->modules[i][I_SLOT] < 1 || state->modules[i][I_SLOT] > 3) {
            badTimedModules++;
        }
    }
    return 10 * collisions_1 + 10 * collisions_2 + 10 * collisions_3 + badTimedModules;
}

void StundenplanProblem::cross(Stundenplan *a, Stundenplan *b, Stundenplan *out) {
    for (int i = 0; i < TOTAL_MODULES; i++) {
        out->modules[i][0] = getRandomBool() ? a->modules[i][0] : b->modules[i][0]; //Random Day from A or B
        out->modules[i][1] = getRandomBool() ? a->modules[i][1] : b->modules[i][1]; //Random Slot from A or B
        out->modules[i][2] = getRandomBool() ? a->modules[i][2] : b->modules[i][2]; //Random Room from A or B
    }
}

void StundenplanProblem::mutate(Stundenplan *instance, float rate) {
    for (int i = 0; i < TOTAL_MODULES; i++) {
        if (getRandomFloat() < rate) {
            instance->modules[i][I_DAY] = getNumberInRange(0, DAYS_IN_WEEK - 1); //Day
        }
        if (getRandomFloat() < rate) {
            instance->modules[i][I_SLOT] = getNumberInRange(0, SLOTS_PER_DAY - 1); //Slot
        }
        if (getRandomFloat() < rate) {
            instance->modules[i][I_ROOM] = getNumberInRange(0, MAX_ROOMS - 1); //Room
        }
    }
}

bool StundenplanProblem::isGoal(Stundenplan *state) {
    //Function will never find the perfect solution, so it will always return false.
    //Maybe it will find a near perfect solution.
    return calcFitness(state) == 0;
}

bool StundenplanProblem::compare(Stundenplan &a, Stundenplan &b) {
    return calcFitness(&a) < calcFitness(&b);
}

void StundenplanProblem::display(Stundenplan *state) {

    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s:\n", Workdays[i]);
        for (int j = 0; j < SLOTS_PER_DAY; j++) {
            printf("Slot %d (%02d-%02d): ", j, 8 + j * 2, 8 + (j + 1) * 2);
            for (int k = 0; k < TOTAL_MODULES; k++) {
                if (state->modules[k][I_DAY] == i && state->modules[k][I_SLOT] == j) {
                    printf("%s (@Room-%02d, %s), ", Modules[k], state->modules[k][I_ROOM], getLecturerName(k));
                }
            }
            printf("\n");
        }
    }
}

bool validateValues(Stundenplan* plan) {
    for(int i = 0; i < TOTAL_MODULES; i++) {
        if(plan->modules[i][I_DAY] < 0 || plan->modules[i][I_DAY] > DAYS_IN_WEEK - 1) {
            printf("Invalid Day: %d (i: %d)\n", plan->modules[i][I_DAY], i);
            return false;
        }
        if(plan->modules[i][I_SLOT] < 0 || plan->modules[i][I_SLOT] > SLOTS_PER_DAY - 1) {
            printf("Invalid Slot: %d (i: %d)\n", plan->modules[i][I_DAY], i);
            return false;
        }
        if(plan->modules[i][I_ROOM] < 0 || plan->modules[i][I_ROOM] > MAX_ROOMS - 1) {
            printf("Invalid Room: %d (i: %d)\n", plan->modules[i][I_DAY], i);
            return false;
        }
    }
    return true;
}

