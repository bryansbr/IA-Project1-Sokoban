/*

Nombre del archivo: BFSAgent.cpp
Fecha de creación: 02/11/2020
Fecha de modificación: 13/11/2019
Autores: Bryan Steven Biojó - 1629366
         Julián Andrés Castaño - 1625743

*/

#include "BFSAgent.h"

BFSAgent::BFSAgent(int numBoxesIn, int* pos, int** initBoxesPosIn, vector<string>* boardIn) {	
	board =* boardIn;
    numBoxes = numBoxesIn;
    Vertex* vtx = new Vertex(pos, initBoxesPosIn, 0);
	vertx.push(vtx);
}

BFSAgent::~BFSAgent() {

}

//Esta función identifica las posiciones de los objetivos a los que deben llegar las cajas
void BFSAgent::identifyTargets() {
	int band = 0;
	targets = new int*[numBoxes];

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 'X') {
				targets[band] = new int[2];
				targets[band][0] = i;
				targets[band][1] = j;
				band++;
			}
		}
	}
}

bool BFSAgent::searchBox(int posA, int posB, Vertex* vtx) {
	for (int i = 0; i < numBoxes; i++) {
		if (vtx -> getBoxesPos(i, 0) == posA && vtx -> getBoxesPos(i, 1) == posB) {
			return true;
		}
	}
	return false;
}

bool BFSAgent::checkObstacle(int posA, int posB, Vertex* vtx) {
	if (posA < 0 || posB < 0 || posA >= board.size() || posB >= board[0].length()) {
		return true;
	} else if (board[posA][posB] == 'W' || searchBox(posA, posB, vtx)) {
		return true;
	} else {
		return false;
	}
}

bool BFSAgent::expand(Vertex* vtx, char move) {
	switch (move) {
		case 'U':
			if (board[vtx -> getPlayerPos(0)-1][vtx -> getPlayerPos(1)] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0)-1, vtx -> getPlayerPos(1), vtx) && checkObstacle(vtx -> getPlayerPos(0)-2, vtx -> getPlayerPos(1), vtx)) {
				return false;
			} else {
				return true;
			}
		break;

		case 'D':
			if (board[vtx -> getPlayerPos(0)+1][vtx -> getPlayerPos(1)] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0)+1, vtx -> getPlayerPos(1), vtx) && checkObstacle(vtx -> getPlayerPos(0)+2, vtx -> getPlayerPos(1), vtx)) {
				return false;
			} else {
				return true;
			}
		break;

		case 'L':
			if (board[vtx -> getPlayerPos(0)][vtx -> getPlayerPos(1)-1] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1)-1, vtx) && checkObstacle(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1)-2, vtx)) {
				return false;
			} else {
				return true;
			}
		break;

		case 'R':
			if (board[vtx -> getPlayerPos(0)][vtx -> getPlayerPos(1)+1] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1)+1, vtx) && checkObstacle(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1)+2, vtx)) {
				return false;
			} else {
				return true;
			}
		break;
	}
	return false;
}

int** BFSAgent::moveBox(Vertex* vtx, int* pos, char action){
	int** newBoxes = new int*[numBoxes];
	
	for (int i = 0; i < numBoxes; i++) {
		newBoxes[i] = new int [2];
		newBoxes[i][0] = vtx -> getBoxesPos(i, 0);
		newBoxes[i][1] = vtx -> getBoxesPos(i, 1);

		if (vtx -> getBoxesPos(i, 0) == pos[0] && vtx -> getBoxesPos(i, 1) == pos[1]) {
			switch (action){
				case 'U':
					newBoxes[i][0] = newBoxes[i][0]-1;
				break;

				case 'D':
					newBoxes[i][0] = newBoxes[i][0]+1;
				break;

				case 'L':
					newBoxes[i][1] = newBoxes[i][1]-1;
				break;

				case 'R':
					newBoxes[i][1] = newBoxes[i][1]+1;
				break;
			}
		}
	}
	return newBoxes;
}

bool BFSAgent::checkExploredBoxes(Vertex* vtx, int** boxes) {
	for (int  i = 0; i < numBoxes; i++) {
		if (vtx -> getBoxesPos(i, 0) != boxes[i][0] || vtx -> getBoxesPos(i, 1) != boxes[i][1]) {
			return false;
		}
	}
	return true;
}

bool BFSAgent::checkExplored(int* pos, int ** boxes) {
	for (int i = 0; i < explored.size(); i++) {
		if(explored[i] -> getPlayerPos(0) == pos[0] && explored[i] -> getPlayerPos(1) == pos[1] && checkExploredBoxes(explored[i], boxes)) {
			return false;
		}
	}
	return true;
}

void BFSAgent::expandVertex(){
	Vertex* actualVertex = vertx.front();
	vertx.pop();
	if (expand(actualVertex, 'U')) {
		int* pos = new int[2];
		int** boxes = moveBox(actualVertex, pos, 'U');
		pos[0] = actualVertex -> getPlayerPos(0)-1;
		pos[1] = actualVertex -> getPlayerPos(1);

		if(checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, actualVertex -> getDepthTree()+1, actualVertex -> getPath().append("U"));
			vertx.push(vtx);
		}
	}
	if(expand(actualVertex, 'D')) {
		int* pos = new int[2];
		int** boxes = moveBox(actualVertex, pos, 'D');
		pos[0] = actualVertex -> getPlayerPos(0)+1;
		pos[1] = actualVertex -> getPlayerPos(1);
		
		if(checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, actualVertex -> getDepthTree()+1, actualVertex -> getPath().append("D"));
			vertx.push(vtx);
		}
	}
	if(expand(actualVertex, 'L')) {
		int* pos = new int[2];
		int** boxes = moveBox(actualVertex, pos, 'L');
		pos[0] = actualVertex -> getPlayerPos(0);
		pos[1] = actualVertex -> getPlayerPos(1)-1;

		if(checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, actualVertex -> getDepthTree()+1, actualVertex -> getPath().append("L"));
			vertx.push(vtx);
		}
	}
	if(expand(actualVertex, 'R')) {
		int* pos = new int[2];
		int** boxes = moveBox(actualVertex, pos, 'R');
		pos[0] = actualVertex -> getPlayerPos(0);
		pos[1] = actualVertex -> getPlayerPos(1)+1;

		if(checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, actualVertex -> getDepthTree()+1, actualVertex -> getPath().append("R"));
			vertx.push(vtx);
		}
	}	
}

bool BFSAgent::isSolve(){
	int count = 0;
	for (int i = 0; i < numBoxes; i++) {
		if (searchBox(targets[i][0], targets[i][1], vertx.front())) {
			count++;
		}
	}	
	if (count == numBoxes) {
		return true;
	} else {
		return false;
	}	
}

string BFSAgent::startSearch(){ // Update...
	do {
		if (vertx.front() -> getDepthTree() >= 64) {
			vertx.pop();
		} else {
			explored.push_back(vertx.front());
			expandVertex();
		}
	} while (!isSolve());
	return	vertx.front() -> getPath(); 
}