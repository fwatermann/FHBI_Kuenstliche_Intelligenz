//
// Created by finnw on 14.11.2022.
//

#ifndef POSTER_1_STUNDENPLAN_HPP
#define POSTER_1_STUNDENPLAN_HPP

#define MODULES_TOTAL 16
#define DAYS_IN_WEEK 5
#define SLOTS_PER_DAY 6
#define MAX_ROOMS 2

#define I_DAY 0
#define I_SLOT 1
#define I_ROOM 2

#include "GeneticAlgorithm.hpp"

static const char* Workdays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

static const char *Modules[] = {"Mathematik 1",
                         "Einfuehrung in die Programmierung mit Skriptsprachen",
                         "Technische Informatik",
                         "Einfuehrung in die Informatik",
                         "Objektorientierte Programmierung",
                         "Datenbanken",
                         "Software Engineering",
                         "Embedded Systems",
                         "Systemprogrammierung",
                         "Softwareprojektmanagement",
                         "Sicherheit und Zuverlaessigkeit",
                         "Webengineering",
                         "Compilerbau",
                         "Kuenstliche Intelligenz",
                         "Computer Vision",
                         "Technical English"
};

static const char *Lecturers[] = {"George BC",
                           "Kreienkamp Angela",
                           "Behrens Grit",
                           "Rexilius Jan",
                           "Becking Dominic",
                           "Brunsmann Jörg",
                           "König Matthias",
                           "Gips Carsten",
                           "Teich Irene",
                           "Thiel Christoph",
                           "Demir Hüseyin"
};

static const int ModuleLecturer[][2] = {{0,  0},
                                 {1,  0},
                                 {2,  1},
                                 {3,  2},
                                 {4,  3},
                                 {5,  4},
                                 {6,  5},
                                 {7,  6},
                                 {8,  7},
                                 {9,  8},
                                 {10, 9},
                                 {11, 2},
                                 {12, 0},
                                 {12, 7},
                                 {13, 7},
                                 {14, 3},
                                 {15, 10}
};

static const int ModuleSemester[] = {1,1,1,1,1,3,3,3,3,3,5,5,5,5,5,5};


struct Stundenplan {
    int modules[MODULES_TOTAL][3]; //Day, Slot, Room
    int calculateFitness();
};

bool doLecturerOverlap(int moduleA, int moduleB);

class StundenplanProblem : public KI::GeneticAlgorithm::Problem<Stundenplan> {

    public:
        StundenplanProblem(float mutatRate, int popSize, int maxGens)
            : KI::GeneticAlgorithm::Problem<Stundenplan>(mutatRate, popSize, maxGens, compare) {}

        bool isGoal(Stundenplan *state) override;
        void cross(Stundenplan* a, Stundenplan* b, Stundenplan* out) override;
        void mutate(Stundenplan* instance, float rate) override;
        void generateRandom(Stundenplan* out) override;

        static bool compare(Stundenplan &a, Stundenplan &b);
        void display(Stundenplan *state) override;
};


#endif //POSTER_1_STUNDENPLAN_HPP
