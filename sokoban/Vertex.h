/*

File name: Vertex.h
Creation date: 02/11/2020
Modification date: 15/11/2020
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 1623447
		 Juan Pablo Rendón      - 1623049

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
        int* playerPos = new int[2];
        int** boxesPos;
        int depthTree;
        string path = " ";
        bool isLeaf;
    public:
        Vertex(int * playerPosIn, int ** initBoxesPosIn, int depthTreeIn);
        Vertex(int * playerPosIn, int ** initBoxesPosIn, int depthTreeIn, string route);
        ~Vertex();
        // Getters
        int getPlayerPos(int a);
        int getBoxesPos(int i, int j);
        int getDepthTree();
        string getPath();
        void deletePos();       
};

#endif