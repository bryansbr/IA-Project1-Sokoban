/*

File name: Vertex.h
Creation date: 02/11/2020
Modification date: 15/11/2020
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 
		 El otro men xd         - 

*/

#ifndef VERTEX_H
#define VERTEX_H

// Libraries
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Defining the parameters of the vertex or node
class Vertex {
    private:
        int * playerPos = new int[2];
        int ** boxesPos;
        int depthTree;
        string path = "";
        bool isLeaf;
    public:
        Vertex(int * playerPosIn, int ** initBoxesPosIn, int treeDepthIn);
        Vertex(int * playerPosIn, int ** initBoxesPosIn, int treeDepthIn, string route);
        ~Vertex();
        // Getters
        int getPlayerPos(int x);
        int getBoxesPos(int i, int j);
        int getDepthTree();
        string getPath();
        void deletePos();       
};

#endif