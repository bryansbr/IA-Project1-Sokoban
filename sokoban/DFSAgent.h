/*

File name: DFSAgent.h
Creation date: 02/11/2020
Modification date: 15/11/2020
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 1623447
		 Juan Pablo Rendón      - 1623049

*/

// Libraries
#ifndef DFSAGENT_H
#define DFSAGENT_H
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "Vertex.h"
using namespace std;

// Defining the parameters of DFS Agent.
class DFSAgent {
    private:
        int numBoxes;
        int** targets;
        stack<Vertex*> vertx;
        vector<Vertex*> explored;
        vector<string> board;
    public:
        DFSAgent(int numBoxesIn, int* pos, int** initBoxesPosIn, vector<string>* boardIn);
        ~DFSAgent();
        void identifyTargets();
        string startSearch();
        bool searchBox(int posA, int posB, Vertex* vtx);
        bool checkObstacle(int posA, int posB, Vertex* vtx);
        int** moveBox(Vertex* vtx, int* pos, char action);
        bool checkExploredBoxes(Vertex* vtx, int** boxes);
        bool expandTree(Vertex* vtx, char move);
        bool checkExplored(int* pos, int** boxes);
        void expandVertex();
        bool isSolve();
};

#endif