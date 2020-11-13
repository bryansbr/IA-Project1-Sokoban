/*

Nombre del archivo: Vertex.cpp
Fecha de creación: 02/11/2020
Fecha de modificación: 13/11/2019
Autores: Bryan Steven Biojó - 1629366
         Julián Andrés Castaño - 1625743

*/

#include "Vertex.h"

// Setters
Vertex::Vertex(int * playerPosIn, int ** initBoxesPosIn, int treeDepthIn) {
	playerPos = playerPosIn;
	boxesPos = initBoxesPosIn;
	depthTree = treeDepthIn;
}

Vertex::Vertex(int * playerPosIn,int ** initBoxesPosIn, int treeDepthIn, string route) {
	playerPos = playerPosIn;
	boxesPos = initBoxesPosIn;
	depthTree = treeDepthIn;
	path = route;
}

Vertex::~Vertex() { // Destructor
	
}

// Getters
int Vertex::getPlayerPos(int x) {
	return playerPos[x];
}

int Vertex::getBoxesPos(int i, int j) {
	return boxesPos[i][j];
}

int Vertex::getDepthTree() {
	return depthTree;
}

string Vertex::getPath() {
	return path;
}

void Vertex::deletePos() {
	delete [] playerPos;
	delete [] boxesPos;
}
