/*

File name: BFSAgent.cpp
Creation date: 02/11/2020
Modification date: 15/11/2020
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 
		 El otro men xd         - 

*/

// Libraries
#include "BFSAgent.h"

// Constructor method.
BFSAgent::BFSAgent(int numBoxesIn, int* pos, int** initBoxesPosIn, vector<string>* boardIn) {	
	board =* boardIn;
    numBoxes = numBoxesIn;
    Vertex* vtx = new Vertex(pos, initBoxesPosIn, 0);
	vertx.push(vtx);
}

// Destructor method.
BFSAgent::~BFSAgent() {

}

// This method identifies the positions of the targets that the boxes must reach.
void BFSAgent::identifyTargets() {
	int flag = 0;
	targets = new int*[numBoxes];
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 'X') {
				targets[flag] = new int[2];
				targets[flag][0] = i;
				targets[flag][1] = j;
				flag++;
			}
		}
	}
}

// This method starts the tree search.
string BFSAgent::startSearch() {
	while (!isSolve()) {
		if (vertx.front() -> getDepthTree() >= 64) { // Tree depth restricted to level 64.
			vertx.pop();
		} else {
			explored.push_back(vertx.front());
			expandVertex();
		}
	}
	return vertx.front() -> getPath(); 
}

// This method is in charge of searching the boxes in the board.
bool BFSAgent::searchBox(int posA, int posB, Vertex* vtx) {
	for (int i = 0; i < numBoxes; i++) {
		if (vtx -> getBoxesPos(i, 0) == posA && vtx -> getBoxesPos(i, 1) == posB) {
			return true;
		}
	}
	return false;
}

// This method identify if the are obstacles in the board.
bool BFSAgent::checkObstacle(int posA, int posB, Vertex* vtx) {
	if (posA < 0 || posB < 0 || posA >= board.size() || posB >= board[0].length()) {
		return true;
	} else if (board[posA][posB] == 'W' || searchBox(posA, posB, vtx)) {
		return true;
	} else {
		return false;
	}
}

// This method is in charge of move the boxes in the board.
int** BFSAgent::moveBox(Vertex* vtx, int* pos, char action){
	int** newBoxes = new int*[numBoxes];
	for (int i = 0; i < numBoxes; i++) {
		newBoxes[i] = new int[2];
		newBoxes[i][0] = vtx -> getBoxesPos(i, 0);
		newBoxes[i][1] = vtx -> getBoxesPos(i, 1);
		if (vtx -> getBoxesPos(i, 0) == pos[0] && vtx -> getBoxesPos(i, 1) == pos[1]) {
			switch (action){
				case 'U':
					newBoxes[i][0] = newBoxes[i][0] - 1;
				break;
				case 'D':
					newBoxes[i][0] = newBoxes[i][0] + 1;
				break;
				case 'L':
					newBoxes[i][1] = newBoxes[i][1] - 1;
				break;
				case 'R':
					newBoxes[i][1] = newBoxes[i][1] + 1;
				break;
				default:
					"Error. Invalid move!";
			}
		}
	}
	return newBoxes;
}

// This method verify if the boxes in the board were explored.
bool BFSAgent::checkExploredBoxes(Vertex* vtx, int** boxes) {
	for (int i = 0; i < numBoxes; i++) {
		if (vtx -> getBoxesPos(i, 0) != boxes[i][0] || vtx -> getBoxesPos(i, 1) != boxes[i][1]) {
			return false;
		}
	}
	return true;
}

// This method is in charge of specifying the move cases: U, D, L, R (in BFS order).
bool BFSAgent::expandTree(Vertex* vtx, char move) {
	switch (move) {
		case 'U':
			if (board[vtx -> getPlayerPos(0) - 1][vtx -> getPlayerPos(1)] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0) - 1, vtx -> getPlayerPos(1), vtx) && checkObstacle(vtx -> getPlayerPos(0) - 2, vtx -> getPlayerPos(1), vtx)) {
				return false;
			} else {
				return true;
			}
		break;
		case 'D':
			if (board[vtx -> getPlayerPos(0) + 1][vtx -> getPlayerPos(1)] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0) + 1, vtx -> getPlayerPos(1), vtx) && checkObstacle(vtx -> getPlayerPos(0) + 2, vtx -> getPlayerPos(1), vtx)) {
				return false;
			} else {
				return true;
			}
		break;
		case 'L':
			if (board[vtx -> getPlayerPos(0)][vtx -> getPlayerPos(1) - 1] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1) - 1, vtx) && checkObstacle(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1) - 2, vtx)) {
				return false;
			} else {
				return true;
			}
		break;
		case 'R':
			if (board[vtx -> getPlayerPos(0)][vtx -> getPlayerPos(1) + 1] == 'W') {
				return false;
			} else if (searchBox(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1) + 1, vtx) && checkObstacle(vtx -> getPlayerPos(0), vtx -> getPlayerPos(1) + 2, vtx)) {
				return false;
			} else {
				return true;
			}
		break;
		default:
			"Error. Invalid move!";
	}
	return false;
}

// This method verify if a position in the board were explored.
bool BFSAgent::checkExplored(int* pos, int ** boxes) {
	for (int i = 0; i < explored.size(); i++) {
		if (explored[i] -> getPlayerPos(0) == pos[0] && explored[i] -> getPlayerPos(1) == pos[1] && checkExploredBoxes(explored[i], boxes)) {
			return false;
		}
	}
	return true;
}

// This method expand the vertex in the tree.
void BFSAgent::expandVertex() {
	Vertex* currentVertex = vertx.front();
	vertx.pop();
	if (expandTree(currentVertex, 'U')) {
		int* pos = new int[2];
		pos[0] = currentVertex -> getPlayerPos(0) - 1;
		pos[1] = currentVertex -> getPlayerPos(1);
		int** boxes = moveBox(currentVertex, pos, 'U');
		if (checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, currentVertex -> getDepthTree() + 1, currentVertex -> getPath().append("U"));
			vertx.push(vtx);
		}
	}
	if (expandTree(currentVertex, 'D')) {
		int* pos = new int[2];
		pos[0] = currentVertex -> getPlayerPos(0) + 1;
		pos[1] = currentVertex -> getPlayerPos(1);
		int** boxes = moveBox(currentVertex, pos, 'D');
		if (checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, currentVertex -> getDepthTree() + 1, currentVertex -> getPath().append("D"));
			vertx.push(vtx);
		}
	}
	if (expandTree(currentVertex, 'L')) {
		int* pos = new int[2];
		pos[0] = currentVertex -> getPlayerPos(0);
		pos[1] = currentVertex -> getPlayerPos(1) - 1;
		int** boxes = moveBox(currentVertex, pos, 'L');		
		if (checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, currentVertex -> getDepthTree() + 1, currentVertex -> getPath().append("L"));
			vertx.push(vtx);
		}
	}
	if (expandTree(currentVertex, 'R')) {
		int* pos = new int[2];
		pos[0] = currentVertex -> getPlayerPos(0);
		pos[1] = currentVertex -> getPlayerPos(1) + 1;
		int** boxes = moveBox(currentVertex, pos, 'R');
		if (checkExplored(pos, boxes)) {
			Vertex* vtx = new Vertex(pos, boxes, currentVertex -> getDepthTree() + 1, currentVertex -> getPath().append("R"));
			vertx.push(vtx);
		}
	}	
}

// This method checks if the tree expansion was done.
bool BFSAgent::isSolve() {
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