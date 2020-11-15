/*

File name: DFSAgent.h
Creation date: 02/11/2020
Modification date: 15/11/2019
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 
		 El otro men xd         - 

*/

#ifndef DFSAGENT_H
#define DFSAGENT_H
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "Vertex.h"
using namespace std;

class DFSAgent{
    private:
        int numBoxes;
        int** targets;
        vector <string> board;
        stack <Vertex*> vertx;
        vector <Vertex*> explored;
    public:
        DFSAgent(int numBoxesIn, int* posIn, int** initBoxesPosIn, vector <string>* boardIn);
        ~DFSAgent();
        void identifyTargets();
        string startSearch();
        bool searchBox(int posA, int posB, Vertex* vtx);
        bool checkObstacle(int posA, int posB, Vertex* vtx);
        int** moveBox(Vertex* vtx, int* posIn, char action);
        bool checkExploredBoxes(Vertex* vtx, int** boxes);
        bool expandTree(Vertex* vtx, char move);
        bool checkExplored(int* posIn, int** boxes);
        void expandVertex();
        bool isSolve();
};

#endif