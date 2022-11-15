# Meilenstein 1.2 (Finn Watermann)

Implementation eines `Genetic Algorithm`

## How to: Projekt bauen

### Windows: Visual Studio 17

**Step 1:** Projektdateien generieren
```
cmake -G "Visual Studio 17 2022" -A x64 -B cmake-build -DCMAKE_BUILD_TYPE=Release .
```

**Step 2:**
VisualStudio Projekt im Ordner `cmake-build` öffnen, bauen und ausführen.

### Windows: MinGW Makefiles

**Step 1:** MinGW Makefile generieren
```
cmake -G "MinGW Makefiles" -B cmake-build -DCMAKE_BUILD_TYPE=Release .
```

**Step 2:** Makefile ausführen
```
cd ./cmake-build && make
```

**Step 3:**
Datei `Meilenstein_1_2.exe` in `cmake-build` ausführen. Sollte sich kein Konsolenfenster, die Datei via Konsole starten.

### Unix: Makefiles

**Step 1:** Unix Makefile generieren
```
cmake -G "Unix Makefiles" -B cmake-build -DCMAKE_BUILD_TYPE=Release .
```

**Step 2:** Makefile ausführen
```
cd ./cmake-build && make
```

**Step 3:**
Datei `Meilenstein_1_2` in `cmake-build` ausführen.

## 8-Queens-Problem

### Kodierung

```cpp
struct Chessboard {   
    int queens[8];
};
```
Das `queens[8]` array repräsentiert pro Index eine Spalte des 8x8 Schachbretts. Wenn also an index `2` eine `4` steht, bedeutet das, dass eine Damen auf Feld `E3`steht.

### Crossover

```cpp
void EightQueens::cross(Chessboard* a, Chessboard* b, Chessboard* out) {
	for(int i = 0; i < 8; i ++) {  
	    out->queens[i] = getRandomBool() ? a->queens[i] : b->queens[i];
	}
}
```
Beim Kreuzen zweier Zustände hat jedes Gen eine 50% Chance von Elternteil A oder Elternteil B zu kommen. `getRandomBool()` ist eine Funktion um einen zufälligen (basierend auf der Bernoulli-Verteilung) Wahrheitswert zu erhalten.

### Mutation
```cpp
void EightQueens::mutate(Chessboard* instance, float rate) {  
    for(int i = 0; i < 8; i ++) {  
        float a = this->perDist(this->generator);  
        if(a <= rate) {    
		    instance->queens[i] = getNumberInRange(0, 7);
        }
    }  
}
```
Jedes Gen eines Individuum hat eine definierte Wahrscheinlichkeit sich pro Generation zu verändern. Dabei erhält das Gen einen neuen zufälligen Wert im vorgesehenen Wertebereich.
`getNumberInRange(0, 7)` ist eine Funktion um eine zufällige Zahl in einem zuvor angegebenen Bereich zu generieren. In diesem Fall handelt es sich um einen Bereich von `[0-7]`.

### Fitnessfunktion
```cpp
int Chessboard::calculateFitness() {  
    int collisions = 0;  
    for(int i = 0; i < 8; i ++) {  
        int column = i;  
        int row = this->queens[i];  
        for(int j = i; j < 8; j ++) {  
            if(i == j) continue;  
            if(this->queens[j] == row) { 
	            //Same row?  
                collisions++;  
            }  
            if(this->queens[j] == j+(row-i)) { 
	            //On diagonal (topLeft->bottomRight)  
                collisions++;  
            }  
            if(this->queens[j] == -j+(row+i)) { 
	            //On diagonal (bottomLeft->topRight)  
                collisions++;  
            }  
            //Same column can not occur based on encoding.  
        }  
    }  
    return collisions;  
}
```
Die Fitness eines Individuums wird berechnet aus der Anzahl an Kollisionen auf dem Spielfeld. Daher je weniger Kollisionen auf dem Spielfeld desto kleiner der Wert der Fitnessfunktion.

Da es für dieses Problem nur eine Bedingung auf dem Feld gibt: `Keine Dame darf eine andere Dame schlagen können` habe ich diese Fitnessfunktion gewählt, da sie genau diesen Wert misst.

### Analyse

| Population Size | Mutation Rate | Max Generation Count | Successfull Count | Successfull % | Avg Generation | Best Result | Duration (in s) |
|-----------------|---------------|----------------------|-------------------|---------------|--------------|-------------|----------|
| 2               | 0,1           | 10                   | 0                 | 0             | 0            | 1           | 0,001    |
| 2               | 0,2           | 10                   | 0                 | 0             | 0            | 2           | 0,001    |
| 2               | 0,3           | 10                   | 0                 | 0             | 0            | 3           | 0,001    |
| 2               | 0,4           | 10                   | 0                 | 0             | 0            | 3           | 0,002    |
| 2               | 0,1           | 50                   | 1                 | 0,01          | 10           | 0           | 0,008    |
| 2               | 0,2           | 50                   | 0                 | 0             | 0            | 2           | 0,008    |
| 2               | 0,3           | 50                   | 0                 | 0             | 0            | 2           | 0,009    |
| 2               | 0,4           | 50                   | 0                 | 0             | 0            | 3           | 0,01     |
| 2               | 0,1           | 75                   | 0                 | 0             | 0            | 1           | 0,012    |
| 2               | 0,2           | 75                   | 1                 | 0,01          | 33           | 0           | 0,012    |
| 2               | 0,3           | 75                   | 1                 | 0,01          | 15           | 0           | 0,014    |
| 2               | 0,4           | 75                   | 0                 | 0             | 0            | 2           | 0,014    |
| 2               | 0,1           | 150                  | 0                 | 0             | 0            | 1           | 0,024    |
| 2               | 0,2           | 150                  | 0                 | 0             | 0            | 1           | 0,026    |
| 2               | 0,3           | 150                  | 1                 | 0,01          | 130          | 0           | 0,028    |
| 2               | 0,4           | 150                  | 0                 | 0             | 0            | 3           | 0,029    |
| 10              | 0,1           | 10                   | 4                 | 0,04          | 5,75         | 0           | 0,013    |
| 10              | 0,2           | 10                   | 1                 | 0,01          | 4            | 0           | 0,014    |
| 10              | 0,3           | 10                   | 3                 | 0,03          | 5,667        | 0           | 0,015    |
| 10              | 0,4           | 10                   | 1                 | 0,01          | 8            | 0           | 0,015    |
| 10              | 0,1           | 50                   | 21                | 0,21          | 32,048       | 0           | 0,053    |
| 10              | 0,2           | 50                   | 18                | 0,18          | 26,722       | 0           | 0,059    |
| 10              | 0,3           | 50                   | 7                 | 0,07          | 34,286       | 0           | 0,066    |
| 10              | 0,4           | 50                   | 3                 | 0,03          | 36,333       | 0           | 0,07     |
| 10              | 0,1           | 75                   | 40                | 0,4           | 35,575       | 0           | 0,068    |
| 10              | 0,2           | 75                   | 37                | 0,37          | 35,432       | 0           | 0,078    |
| 10              | 0,3           | 75                   | 14                | 0,14          | 35,143       | 0           | 0,093    |
| 10              | 0,4           | 75                   | 5                 | 0,05          | 24,2         | 0           | 0,103    |
| 10              | 0,1           | 150                  | 49                | 0,49          | 57,918       | 0           | 0,121    |
| 10              | 0,2           | 150                  | 53                | 0,53          | 71,434       | 0           | 0,139    |
| 10              | 0,3           | 150                  | 27                | 0,27          | 67,333       | 0           | 0,176    |
| 10              | 0,4           | 150                  | 10                | 0,1           | 54,6         | 0           | 0,199    |
| 50              | 0,1           | 10                   | 24                | 0,24          | 5,25         | 0           | 0,076    |
| 50              | 0,2           | 10                   | 25                | 0,25          | 6,32         | 0           | 0,088    |
| 50              | 0,3           | 10                   | 17                | 0,17          | 5,706        | 0           | 0,092    |
| 50              | 0,4           | 10                   | 6                 | 0,06          | 4,667        | 0           | 0,102    |
| 50              | 0,1           | 50                   | 48                | 0,48          | 17,646       | 0           | 0,262    |
| 50              | 0,2           | 50                   | 56                | 0,56          | 19,375       | 0           | 0,289    |
| 50              | 0,3           | 50                   | 57                | 0,57          | 22,316       | 0           | 0,314    |
| 50              | 0,4           | 50                   | 36                | 0,36          | 28,111       | 0           | 0,404    |
| 50              | 0,1           | 75                   | 45                | 0,45          | 24,178       | 0           | 0,383    |
| 50              | 0,2           | 75                   | 53                | 0,53          | 25,302       | 0           | 0,413    |
| 50              | 0,3           | 75                   | 76                | 0,76          | 26,105       | 0           | 0,352    |
| 50              | 0,4           | 75                   | 46                | 0,46          | 33,609       | 0           | 0,536    |
| 50              | 0,1           | 150                  | 56                | 0,56          | 42,946       | 0           | 0,646    |
| 50              | 0,2           | 150                  | 71                | 0,71          | 39,676       | 0           | 0,594    |
| 50              | 0,3           | 150                  | 88                | 0,88          | 35,511       | 0           | 0,451    |
| 50              | 0,4           | 150                  | 65                | 0,65          | 63,754       | 0           | 0,898    |
| 100             | 0,1           | 10                   | 24                | 0,24          | 4,042        | 0           | 0,16     |
| 100             | 0,2           | 10                   | 37                | 0,37          | 5,405        | 0           | 0,172    |
| 100             | 0,3           | 10                   | 27                | 0,27          | 6,667        | 0           | 0,201    |
| 100             | 0,4           | 10                   | 17                | 0,17          | 6,647        | 0           | 0,218    |
| 100             | 0,1           | 50                   | 54                | 0,54          | 14,037       | 0           | 0,491    |
| 100             | 0,2           | 50                   | 60                | 0,6           | 15,35        | 0           | 0,525    |
| 100             | 0,3           | 50                   | 67                | 0,67          | 18,657       | 0           | 0,572    |
| 100             | 0,4           | 50                   | 68                | 0,68          | 21,588       | 0           | 0,644    |
| 100             | 0,1           | 75                   | 48                | 0,48          | 19,917       | 0           | 0,759    |
| 100             | 0,2           | 75                   | 68                | 0,68          | 16,176       | 0           | 0,631    |
| 100             | 0,3           | 75                   | 78                | 0,78          | 23,782       | 0           | 0,685    |
| 100             | 0,4           | 75                   | 79                | 0,79          | 31,797       | 0           | 0,835    |
| 100             | 0,1           | 150                  | 53                | 0,53          | 32,472       | 0           | 1,339    |
| 100             | 0,2           | 150                  | 80                | 0,8           | 40,263       | 0           | 1,082    |
| 100             | 0,3           | 150                  | 94                | 0,94          | 35,489       | 0           | 0,82     |
| 100             | 0,4           | 150                  | 96                | 0,96          | 40,323       | 0           | 0,911    |


- Die Quote der Erfolgreichen Durchläufe steigt, je größer die Population wird. Das liegt womöglich daran, dass pro Generation mehrere Kombinationen an Genen getestet werden können. Ab einer Generationsgröße von `10` wird immer eine Lösung gefunden.
- Bei den kleinen Populationen ist gut zu erkennen, dass eine höhere Mutationsrate zu höheren Erfolgschancen führt.
- Hohe Mutationsraten können in großen Populationen zur Verringerung der Erfolgschance führen
- Durchlaufdauer größer je größer die Population

## Landkarten-Färbeproblem
![[assets/map.png]]
### Kodierung
```cpp
struct Karte {
	int colors[6];
}
```
Das `colors[6]` array repräsentiert pro Index ein Land auf der Karte. Wenn also an index `2` eine `4` steht, bedeutet das, dass Feld `2` die Farbe `4` hat.

### Crossover
```cpp
void KartenFaerben::cross(Karte *a, Karte *b, Karte *out) {  
    for(int i = 0; i < 6; i ++) {  
        out->colors[i] = getRandomBool() ? a->colors[i] : b->colors[i];  
    }  
}
```
Jedes Gen des Kindes wird zufällig von Elternteil A oder Elternteil B übernommen.

### Mutation
```cpp
void KartenFaerben::mutate(Karte *instance, float rate) {  
    for(int i = 0; i < 6; i ++) {  
        float a = getRandomFloat();  
        if(a <= rate) {  
            instance->colors[i] = getNumberInRange(0, 5);  
        }  
    }  
}
```
Jedes Gen eines Individuum hat eine definierte Wahrscheinlichkeit sich pro Generation zu verändern. Dabei erhält das Gen einen neuen zufälligen Wert im vorgesehenen Wertebereich.  
`getNumberInRange(0, 5)` ist eine Funktion um eine zufällige Zahl in einem zuvor angegebenen Bereich zu generieren. In diesem Fall handelt es sich um einen Bereich von `[0 - 5]`.

### Fitnessfunktion

```cpp
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
```
Um die Fitness eines Individuums festzustellen wird die Anzahl an verwendeten Farben und die Anzahl an Konflikten zusammengerechnet. Dabei fällt die Anzahl der Konflikte **vierfach** ins Gewicht um den Algorithmus anzuregen die Konflikte "erst" zu lösen.

### Analyse

| Population Size | Mutation Rate | Max Generation Count | Successfull Count | Successfull % | Avg Generation | Best Result | Duration |
|-----------------|---------------|----------------------|-------------------|---------------|--------------|-------------|----------|
| 2               | 0,1           | 10                   | 23                | 23%           | 5,261        | 3           | 0,004    |
| 2               | 0,2           | 10                   | 31                | 31%           | 5,839        | 3           | 0,003    |
| 2               | 0,3           | 10                   | 31                | 31%           | 4,581        | 3           | 0,003    |
| 2               | 0,4           | 10                   | 38                | 38%           | 3,895        | 3           | 0,003    |
| 2               | 0,1           | 50                   | 67                | 67%           | 18,791       | 3           | 0,008    |
| 2               | 0,2           | 50                   | 84                | 84%           | 17,786       | 3           | 0,006    |
| 2               | 0,3           | 50                   | 86                | 86%           | 16,349       | 3           | 0,006    |
| 2               | 0,4           | 50                   | 88                | 88%           | 17,08        | 3           | 0,006    |
| 2               | 0,1           | 75                   | 85                | 85%           | 28,224       | 3           | 0,01     |
| 2               | 0,2           | 75                   | 90                | 90%           | 27,289       | 3           | 0,009    |
| 2               | 0,3           | 75                   | 97                | 97%           | 22,794       | 3           | 0,008    |
| 2               | 0,4           | 75                   | 95                | 95%           | 20,011       | 3           | 0,007    |
| 2               | 0,1           | 150                  | 97                | 97%           | 31,103       | 3           | 0,01     |
| 2               | 0,2           | 150                  | 100               | 100%          | 29,68        | 3           | 0,008    |
| 2               | 0,3           | 150                  | 99                | 99%           | 22,152       | 3           | 0,007    |
| 2               | 0,4           | 150                  | 100               | 100%          | 31,39        | 3           | 0,009    |
| 10              | 0,1           | 10                   | 76                | 76%           | 3,289        | 3           | 0,018    |
| 10              | 0,2           | 10                   | 88                | 88%           | 3,341        | 3           | 0,016    |
| 10              | 0,3           | 10                   | 98                | 98%           | 2,949        | 3           | 0,013    |
| 10              | 0,4           | 10                   | 95                | 95%           | 2,989        | 3           | 0,014    |
| 10              | 0,1           | 50                   | 100               | 100%          | 5,63         | 3           | 0,02     |
| 10              | 0,2           | 50                   | 100               | 100%          | 4,27         | 3           | 0,016    |
| 10              | 0,3           | 50                   | 100               | 100%          | 3,67         | 3           | 0,017    |
| 10              | 0,4           | 50                   | 100               | 100%          | 3,77         | 3           | 0,017    |
| 10              | 0,1           | 75                   | 100               | 100%          | 5,61         | 3           | 0,02     |
| 10              | 0,2           | 75                   | 100               | 100%          | 4,22         | 3           | 0,017    |
| 10              | 0,3           | 75                   | 100               | 100%          | 3,91         | 3           | 0,016    |
| 10              | 0,4           | 75                   | 100               | 100%          | 3,69         | 3           | 0,016    |
| 10              | 0,1           | 150                  | 100               | 100%          | 6,66         | 3           | 0,025    |
| 10              | 0,2           | 150                  | 100               | 100%          | 4,19         | 3           | 0,017    |
| 10              | 0,3           | 150                  | 100               | 100%          | 3,78         | 3           | 0,015    |
| 10              | 0,4           | 150                  | 100               | 100%          | 3,16         | 3           | 0,014    |
| 50              | 0,1           | 10                   | 100               | 100%          | 0,55         | 3           | 0,053    |
| 50              | 0,2           | 10                   | 100               | 100%          | 0,7          | 3           | 0,057    |
| 50              | 0,3           | 10                   | 100               | 100%          | 0,66         | 3           | 0,057    |
| 50              | 0,4           | 10                   | 100               | 100%          | 0,65         | 3           | 0,056    |
| 50              | 0,1           | 50                   | 100               | 100%          | 0,59         | 3           | 0,053    |
| 50              | 0,2           | 50                   | 100               | 100%          | 0,47         | 3           | 0,051    |
| 50              | 0,3           | 50                   | 100               | 100%          | 0,59         | 3           | 0,054    |
| 50              | 0,4           | 50                   | 100               | 100%          | 0,66         | 3           | 0,056    |
| 50              | 0,1           | 75                   | 100               | 100%          | 0,92         | 3           | 0,061    |
| 50              | 0,2           | 75                   | 100               | 100%          | 0,69         | 3           | 0,058    |
| 50              | 0,3           | 75                   | 100               | 100%          | 0,7          | 3           | 0,058    |
| 50              | 0,4           | 75                   | 100               | 100%          | 0,55         | 3           | 0,054    |
| 50              | 0,1           | 150                  | 100               | 100%          | 0,77         | 3           | 0,056    |
| 50              | 0,2           | 150                  | 100               | 100%          | 0,62         | 3           | 0,055    |
| 50              | 0,3           | 150                  | 100               | 100%          | 0,67         | 3           | 0,057    |
| 50              | 0,4           | 150                  | 100               | 100%          | 0,51         | 3           | 0,053    |
| 100             | 0,1           | 10                   | 100               | 100%          | 0,27         | 3           | 0,107    |
| 100             | 0,2           | 10                   | 100               | 100%          | 0,14         | 3           | 0,099    |
| 100             | 0,3           | 10                   | 100               | 100%          | 0,25         | 3           | 0,105    |
| 100             | 0,4           | 10                   | 100               | 100%          | 0,16         | 3           | 0,1      |
| 100             | 0,1           | 50                   | 100               | 100%          | 0,19         | 3           | 0,102    |
| 100             | 0,2           | 50                   | 100               | 100%          | 0,26         | 3           | 0,106    |
| 100             | 0,3           | 50                   | 100               | 100%          | 0,25         | 3           | 0,105    |
| 100             | 0,4           | 50                   | 100               | 100%          | 0,22         | 3           | 0,103    |
| 100             | 0,1           | 75                   | 100               | 100%          | 0,22         | 3           | 0,103    |
| 100             | 0,2           | 75                   | 100               | 100%          | 0,26         | 3           | 0,106    |
| 100             | 0,3           | 75                   | 100               | 100%          | 0,24         | 3           | 0,104    |
| 100             | 0,4           | 75                   | 100               | 100%          | 0,34         | 3           | 0,11     |
| 100             | 0,1           | 150                  | 100               | 100%          | 0,24         | 3           | 0,103    |
| 100             | 0,2           | 150                  | 100               | 100%          | 0,3          | 3           | 0,107    |
| 100             | 0,3           | 150                  | 100               | 100%          | 0,31         | 3           | 0,108    |
| 100             | 0,4           | 150                  | 100               | 100%          | 0,25         | 3           | 0,104    |

- Auch bei schon kleiner Populationsgröße und wenigen maximalen Generationen werden schon Lösungen gefunden, da das Problem nicht sonderlich komplex ist.
- Ab einer Generationsgröße von `10` und einer Maximalen Generations Anzahl von `50` wird immer eine Lösung gefunden.
- Durchlaufdauer größer je größer die Population
- Je größer die Population desto wahrscheinlicher ist es, dass direkt am Start schon eine korrekte Lösung dabei ist. Daher ist der Durchschnitt an benötigten Generationen `unter 0`