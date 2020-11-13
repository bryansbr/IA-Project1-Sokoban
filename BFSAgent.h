/*

Nombre del archivo: BFSAgent.h
Fecha de creación: 02/11/2020
Fecha de modificación: 13/11/2019
Autores: Bryan Steven Biojó - 1629366
         Julián Andrés Castaño - 1625743

*/

#ifndef BFSAGENT_H
#define BFSAGENT_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "Vertex.h"
using namespace std;

class BFSAgent {
    private:
        int numBoxes;
        int** targets;
        vector <string> table;
        queue <Vertex*> vertx;
        vector <Vertex*> explored;

    public:
        BFSAgent(int numBoxesIn, int* pos, int** initBoxesPosIn, vector <string>* table);
        ~BFSAgent();
        int** moveBox(Vertex* vtx, int* pos, char action);
        bool searchBox(int posA, int posB, Vertex* vtx);
        bool checkObstacle(int posA, int posB, Vertex* vtx);
        bool expand(Vertex* vtx, char move);
        bool checkExplored(int* pos, int** boxes);
        bool checkExploredBoxes(Vertex* vtx, int** boxes);
        bool isSolve();
        string startSearch();
        void identifyTargets();
        void expandVertex();
};

#endif