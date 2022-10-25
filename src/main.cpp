#include "EightQueens.hpp"
#include <chrono>
#include <vector>

int main() {

    std::vector<int> popSize = {2, 10, 50};
    std::vector<int> maxGens = {10, 50, 75};
    std::vector<float> mutatRate = {0.1f, 0.2f, 0.3f};
    int repeat = 100;

    //setbuf(stdout, NULL);

    std::chrono::steady_clock::time_point gStart = std::chrono::steady_clock::now();
    for (int i = 0; i < popSize.size(); i++) {
        for (int j = 0; j < maxGens.size(); j++) {
            for (int k = 0; k < mutatRate.size(); k++) {

                int successCounter = 0;
                int generationsNeeded = 0;

                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                for (int r = 0; r < repeat; r++) {
                    EightQueens eq = EightQueens(mutatRate[k], popSize[i], maxGens[j]);
                    std::pair<Chessboard *, int> result = eq.solve();
                    if (result.first != nullptr) {
                        successCounter++;
                        generationsNeeded += result.second;
                    }
                    printf(".");
                }
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

                printf("PopSize: %d, MutatRate: %f, MaxGens: %d, SuccessRate: %f, GenAvg: %f [%lld s]\n", popSize[i],
                       mutatRate[k], maxGens[j], (float) successCounter / (float) repeat,
                       (float) generationsNeeded / (float) successCounter,
                       std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
            }
        }
    }
    std::chrono::steady_clock::time_point gEnd = std::chrono::steady_clock::now();

    printf("Gesamt Dauer: %lld s\n", std::chrono::duration_cast<std::chrono::seconds>(gEnd - gStart).count());

    return 0;
}
