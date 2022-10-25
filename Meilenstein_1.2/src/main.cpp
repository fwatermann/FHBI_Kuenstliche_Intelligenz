#include "EightQueens.hpp"
#include "KartenFaerben.hpp"
#include <chrono>
#include <vector>

//#define PRINT_CSV

void run8Queens();
void runKartenFaerben();

int main() {

    printf("Available problems: \n");
    printf("\t1. 8-Queens problem\n");
    printf("\t2. Map coloring problem\n\n");

    bool ok = false;
    while(!ok) {
        printf("Select [1-2]: ");

        int input;
        std::cin >> input;

        if(input < 1 || input > 2) {
            printf("\nInvalid input.\n");
            continue;
        }

        printf("\n\n");

        ok = true;

        switch (input) {
            case 1:
                run8Queens();
                break;
            case 2:
                runKartenFaerben();
                break;
            default:
                break;
        }
    }

    return 0;
}

void run8Queens() {

    printf("================================================\n");
    printf("##              8 Queens Problem              ##\n");
    printf("================================================\n\n");

    std::vector<int> popSize = {2, 10, 50, 100};
    std::vector<int> maxGens = {10, 50, 75, 150};
    std::vector<float> mutatRate = {0.1f, 0.2f, 0.3f, 0.4f};
    int repeat = 100;

#ifdef PRINT_CSV
    printf("Population Size;Mutation Rate;Max Anzahl Generationen;Erfolgreich Anzahl;Erfolgreich Prozent;Durchschnitt Generationen;Bestes Ergebnis;Dauer\n");
#endif

    std::chrono::steady_clock::time_point gStart = std::chrono::steady_clock::now();
    for (int i = 0; i < popSize.size(); i++) {
        for (int j = 0; j < maxGens.size(); j++) {
            for (int k = 0; k < mutatRate.size(); k++) {

                int successCounter = 0;
                int generationsNeeded = 0;
                int bestFitness = INT32_MAX;

                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                for (int r = 0; r < repeat; r++) {
                    EightQueens eq = EightQueens(mutatRate[k], popSize[i], maxGens[j]);
                    std::pair<Chessboard *, std::pair<int, int>> result = eq.solve();
                    if (result.first != nullptr) {
                        successCounter++;
                        generationsNeeded += result.second.first;
                    }
                    result.second.second < bestFitness ? bestFitness = result.second.second : bestFitness;
                }
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

#ifndef PRINT_CSV
                printf("PopSize: %d, MutatRate: %.3f, MaxGens: %d, Success: %d (%.3f), GenAvg: %.3f, BestFit: %d [%.3f s]\n", popSize[i],
                       mutatRate[k], maxGens[j], successCounter, (float) successCounter / (float) repeat,
                       successCounter > 0 ? (float)generationsNeeded / (float) successCounter : 0, bestFitness,
                       std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0);
#else
                printf("%d;%.3f;%d;%d;%.3f;%.3f;%d;%.3f\n", popSize[i], mutatRate[k], maxGens[j],
                       successCounter, (float)successCounter/(float)repeat,
                       successCounter > 0 ? (float)generationsNeeded / (float) successCounter : 0, bestFitness,
                       std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / 1000.0);
#endif
            }
        }
    }
    std::chrono::steady_clock::time_point gEnd = std::chrono::steady_clock::now();

    printf("Gesamt Dauer: %lld s\n", std::chrono::duration_cast<std::chrono::seconds>(gEnd - gStart).count());

}

void runKartenFaerben() {

    printf("================================================\n");
    printf("##               KARTEN FAERBEN               ##\n");
    printf("================================================\n\n");

    std::vector<int> popSize = {2, 10, 50, 100};
    std::vector<int> maxGens = {10, 50, 75, 150};
    std::vector<float> mutatRate = {0.1f, 0.2f, 0.3f, 0.4f};
    int repeat = 100;

#ifdef PRINT_CSV
    printf("Population Size;Mutation Rate;Max Anzahl Generationen;Erfolgreich Anzahl;Erfolgreich Prozent;Durchschnitt Generationen;Bestes Ergebnis;Dauer\n");
#endif

    std::chrono::steady_clock::time_point gStart = std::chrono::steady_clock::now();
    for (int i = 0; i < popSize.size(); i++) {
        for (int j = 0; j < maxGens.size(); j++) {
            for (int k = 0; k < mutatRate.size(); k++) {

                int successCounter = 0;
                int generationsNeeded = 0;
                int bestFitness = INT32_MAX;

                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                for (int r = 0; r < repeat; r++) {
                    auto* eq = new KartenFaerben(mutatRate[k], popSize[i], maxGens[j]);
                    std::pair<Karte *, std::pair<int, int>> result = eq->solve();
                    if (result.first != nullptr) {
                        successCounter++;
                        generationsNeeded += result.second.first;
                    }
                    result.second.second < bestFitness ? bestFitness = result.second.second : bestFitness;
                    //printf(".");
                    delete eq;
                }

                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

#ifndef PRINT_CSV
                printf("PopSize: %d, MutatRate: %.3f, MaxGens: %d, Success: %d (%.3f), GenAvg: %.3f, BestFit: %d [%.3f s]\n", popSize[i],
                       mutatRate[k], maxGens[j], successCounter, (float) successCounter / (float) repeat,
                       successCounter > 0 ? (float)generationsNeeded / (float) successCounter : 0, bestFitness,
                       std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0);
#else
                printf("%d;%.3f;%d;%d;%.3f;%.3f;%d;%.3f\n", popSize[i], mutatRate[k], maxGens[j],
                       successCounter, (float)successCounter/(float)repeat,
                       successCounter > 0 ? (float)generationsNeeded / (float) successCounter : 0, bestFitness,
                       std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / 1000.0);
#endif
            }
        }
    }
    std::chrono::steady_clock::time_point gEnd = std::chrono::steady_clock::now();

    printf("Gesamt Dauer: %.3f s\n", std::chrono::duration_cast<std::chrono::milliseconds>(gEnd - gStart).count() / 1000.0);
}
