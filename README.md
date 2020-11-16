# SOKOBAN
Intelligent agent that solves Sokoban boards using AI algorithms: BFS (Breadth-first search), DFS (Depth-first search) and Iterative DFS (Iterative deepening depth-first search).

## Team members
* Bryan Steven Biojó     - 1629366
* Julián Andrés Castaño  - 1625743
* Juan Sebastián Saldaña - 1623447
* Juan Pablo Rendón      - 1623049

The program is able to solve Sokoban boards using BFS and DFS. In the case of IterativeDFS, it presents problems when executing (it takes too long). The scripts are configured to run on Linux operating systems (for Windows it presents some problems). If you want to test IterativeDFS, uncomment the last block of code in the ```main.cpp``` file.

## To run it

1. Enter the **sokoban** folder.
```
cd IA-Project1-Sokoban/sokoban/
```

2. Run:
```
sudo sh build.sh
```

3. Run:
```
sudo sh run.sh nivelN.txt
```
Where *N* represents the number of the level (e.g. ```sudo sh run.sh nivel1.txt```). The (<) symbol is not included in the run (missing).
