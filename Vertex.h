/*

Nombre del archivo: Vertex.h
Fecha de creación: 02/11/2020
Fecha de modificación: 13/11/2019
Autores: Bryan Steven Biojó - 1629366
         Julián Andrés Castaño - 1625743

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
        int * playerPos = new int[2]; // Pointer (...)
        int ** boxesPos; // Double pointer (...)
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
