/*

File name: IterativeDFSAgent.h
Creation date: 02/11/2020
Modification date: 15/11/2020
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 
		 El otro men xd         - 

*/

// Libraries
#ifndef ITERATIVEDFSAGENT_H
#define ITERATIVEDFSAGENT_H
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "Vertex.h"
using namespace std;

// Defining the parameters of Iterative DFS Agent.
class IterativeDFSAgent { 
    private:
        int depthLimit; 
        int numBoxes;
        int** targets;
        Vertex* root;
        stack <Vertex*> vertx;
        vector <string> board;
        vector <Vertex*> explored;
    public:
        IterativeDFSAgent(int numBoxesIn, int* posIn, int** initBoxesPosIn, vector <string>* boardIn);
        ~IterativeDFSAgent();
        void identifyTargets();
        bool searchBox(int posF, int posC, Vertex * node);
        bool expand(Vertex * node ,char move);
        int** moveBox(Vertex * node,int * pos,char accion);
        bool checkObstacle(int posF,int posC,Vertex * node);
        bool isSolve();
        void expandNode();
        bool checkExplored(int* pos, int ** boxes);
        bool checkExploredBoxes(Vertex * node, int ** boxes);

        string iniciarBusqueda();
       

};

#endif