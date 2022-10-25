# Meilenstein 1.1 (Finn Watermann 1252145)

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/ad/MapGermanyGraph.svg/476px-MapGermanyGraph.svg.png" style="max-width: 300px; display: inline-block;">
<img src="https://www.fh-bielefeld.de/elearning/data/FH-Bielefeld/lm_data/lm_1358898/assignments/images/MapGermanyGraph-Kosten.png" style="max-width: 300px; display: inline-block;">

## 1. Tiefen-, Breitensuche & A*

### 1.1 Tiefensuche

```txt
1. [W]
2. [WN-1, WF-1, WE-1] | [W]
3. [WN-1, WF-1] | [W, E]
4. [WN-1, WFMa-2, WFK-2] | [W, E, F]
5. [WN-1, WFMa-2, WFKMü-3] | [W, E, F, K]
6. Ziel erreicht: WFKMü: Würzburg -> Frankfurt -> Kassel -> München (Länge: 3)
```

### 1.2 Breitensuche

```txt
1. [W]
2. [WN, WF, WE] | [W]
3. [WF, WE, WNMü, WNS] | [W, N]
4. [WE, WNMü, WNS, WFK, WFMa] | [W, N, F]
5. [WNMü, WNS, WFK, WFMa] | [W, N, F, E]
6. Ziel erreicht: WNMü: Würzburg -> Nürnberg -> München (Länge: 2)
```

### 1.3 A*

```txt
 >> Nicht möglich <<
```

<div style="page-break-before:always"></div>

### Vergleich

| Verfahren    | Max. markiert | Max. in Datenstruktur | Schleifendurchläufe |
|--------------|---------------|-----------------------|---------------------|
| Tiefensuche  | 4             | 3                     | 5                   |
| Breitensuche | 4             | 5                     | 5                   |
| A*           | -/-           | -/-                   | -/-                 |

## 2. Dürfen die oben gegebenen Restkostenabschätzungen in A* verwendet werden?

Die Restkostenabschätzung sind nicht zulässig für den A* Algorithmus, da `h(n) >= 0` sein muss und dabei die Heuristik den tatsächlichen Weg nicht überschätzt, was hier nicht der fall ist, da `Nürnberg -> München = 167km & h(Nürnberg) = 537km --> 537km > 167km`.

### A* mit korrigierter Heuristik.

| Stadt           | h(n)     |
|-----------------|----------|
| Augsburg (A)    | 0km      |
| Erfurt (E)      | 400 km   |
| Frankfurt (F)   | 100 km   |
| Karlsruhe (Kar) | 10 km    |
| Kassel (Kas)    | 460 km   |
| Mannheim (Ma)   | 200 km   |
| *München* (Mü)  | 0 km     |
| Nürnberg (N)    | `152 km` |
| Stuttgart (S)   | 300 km   |
| *Würzburg* (W)  | 170 km   |

```txt
1. [W-0+170]
2. [WN-103+152, WF-217+100, WE-186+400]
3. [WNMü-270+0, WF-217+100, WNW-206+170, WE-186+400, WNS-286+300]
4. Ziel erriecht: 
    WNMü: Würzburg --103km-> Nürnberg --167km-> München (Länge: 270km)
```
