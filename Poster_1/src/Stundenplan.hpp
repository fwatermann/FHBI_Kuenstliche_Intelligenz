//
// Created by finnw on 14.11.2022.
//

#ifndef POSTER_1_STUNDENPLAN_HPP
#define POSTER_1_STUNDENPLAN_HPP

#define TOTAL_MODULES 16
#define TOTAL_SEMESTERS 3
#define DAYS_IN_WEEK 5
#define SLOTS_PER_DAY 6
#define MAX_ROOMS 2

#define I_DAY 0
#define I_SLOT 1
#define I_ROOM 2

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
    int modules[TOTAL_MODULES][3]; //Day, Slot, Room
};

bool doLecturerOverlap(int moduleA, int moduleB);
char* getLecturerName(int module);

class StundenplanProblem {

    public:
        static bool isGoal(Stundenplan *state);
        static void cross(Stundenplan* a, Stundenplan* b, Stundenplan* out);
        static void mutate(Stundenplan* instance, float rate);
        static void generateRandom(Stundenplan* out);

        static bool compare(Stundenplan &a, Stundenplan &b);
        static void display(Stundenplan *state);
        static int calcFitness(Stundenplan *state);
};




#endif //POSTER_1_STUNDENPLAN_HPP
