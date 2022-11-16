# Poster 1.0 (Finn Watermann)

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