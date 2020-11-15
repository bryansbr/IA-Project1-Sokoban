/*

File name: IterativeDFSAgent.cpp
Creation date: 02/11/2020
Modification date: 15/11/2020
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 
		 El otro men xd         - 

*/

// Libraries
#include "IterativeDFSAgent.h"

// Constructor method
IterativeDFSAgent::IterativeDFSAgent(int numBoxesIn, int* posIn, int** initBoxesPosIn, vector<string> *boardIn) {	
	board =* boardIn;
    numBoxes = numBoxesIn;
    Vertex* vtx = new Vertex(posIn, initBoxesPosIn, 0);
	root = vtx; // Careful!
	vertx.push(vtx); 
}

// Destructor method
IterativeDFSAgent::~IterativeDFSAgent() {

}

// This method identifies the positions of the targets that the boxes must reach.
void IterativeDFSAgent::identifyTargets() {
	int flag = 0;
	targets = new int*[numBoxes];
	for (int i = 0; i < numBoxes; i++) {
		targets[i] = new int[2];
	}
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 'X') {
				targets[flag][0] = i;
				targets[flag][1] = j;
				flag++;
			}
		}
	}
}

// This method starts the tree search.
string IterativeDFSAgent::startSearch() {
	depthLimit = 0;	
	do {
		if (vertx.top() -> getDepthTree() < depthLimit) { // Be careful, check! @bryansbr @AndresDFX...
			expandVertex();	
		} else {
			vertx.pop();
		}
		if (vertx.empty()) {
			depthLimit++;
			for (int j = 0; j < explored.size(); j++) {
				explored.pop_back();
			}
			vertx.push(root);	
		}
	} while (!isSolve());
	return vertx.top() -> getPath();
}

bool IterativeDFSAgent::searchBox(int posF, int posC, Nodo * node){

	for (int i = 0; i < numBoxes; i++){
		
		if(node->getPosBoxes(i,0)==posF && node->getPosBoxes(i,1)==posC)return true;
	}
	
	return false;
}

bool IterativeDFSAgent::checkObstacle(int posF,int posC,Nodo * node){
	if(posF<0 || posC<0 || posF>=board.size() || posC>=board[0].length())return true;
	else if(board[posF][posC]=='W' || searchBox(posF,posC, node)){
		return true;
	}
	else return false;


}

bool IterativeDFSAgent::expand(Nodo * node ,char move){

	switch (move){
		case 'R':
			if(board[node->getPosPlayer(0)][node->getPosPlayer(1)+1]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)+1, node) && checkObstacle(node->getPosPlayer(0),node->getPosPlayer(1)+2,node)) return false;
			else return true;
		break;
		case 'L':
			if(board[node->getPosPlayer(0)][node->getPosPlayer(1)-1]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)-1, node) && checkObstacle(node->getPosPlayer(0),node->getPosPlayer(1)-2,node)) return false;
			else return true;
		break;
		case 'D':
			if(board[node->getPosPlayer(0)+1][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)+1,node->getPosPlayer(1), node) && checkObstacle(node->getPosPlayer(0)+2,node->getPosPlayer(1),node)) return false;
			else return true;
	
		break;
		case 'U':
			if(board[node->getPosPlayer(0)-1][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)-1,node->getPosPlayer(1), node) && checkObstacle(node->getPosPlayer(0)-2,node->getPosPlayer(1),node)) return false;
			else return true;
		break;

	}

	return false;
}


int** IterativeDFSAgent::moveBox(Nodo * node,int * pos,char accion){
	int ** newBoxes = new int *[numBoxes];
	
	for (int i = 0; i < numBoxes; i++){
		newBoxes[i] = new int [2];
		newBoxes[i][0]=node->getPosBoxes(i,0);
		newBoxes[i][1]=node->getPosBoxes(i,1);

		if(node->getPosBoxes(i,0)==pos[0] && node->getPosBoxes(i,1)==pos[1]){
			switch (accion){
				case 'R':
					newBoxes[i][1]=newBoxes[i][1]+1;
				break;
				case 'L':
					newBoxes[i][1]=newBoxes[i][1]-1;
				break;
				case 'D':
					newBoxes[i][0]=newBoxes[i][0]+1;
				break;
				case 'U':
					newBoxes[i][0]=newBoxes[i][0]-1;
				break;
			}
		}
	}
	

	return newBoxes;
}

bool IterativeDFSAgent::checkExploredBoxes(Nodo * node, int ** boxes){
	for (int  i = 0; i < numBoxes; i++){
		if(node->getPosBoxes(i,0)!=boxes[i][0] || node->getPosBoxes(i,1)!=boxes[i][1]) return false;
	}
	return true;
}


bool IterativeDFSAgent::checkExplored(int* pos, int ** boxes){

	for (int i = 0; i < explored.size(); i++){
		if(explored[i]->getPosPlayer(0)==pos[0] &&
		   explored[i]->getPosPlayer(1)==pos[1] &&
		   checkExploredBoxes(explored[i],boxes)
		   ){
			return false;
		}
	}
	return true;

}

void IterativeDFSAgent::expandVertex(){

	if(nodes.top()->getDepthTree()>=64){
		nodes.pop();
		return;
	}

	explored.push_back(nodes.top());

	
	Nodo * actualNode=nodes.top();
	
	nodes.pop();


	if(expand(actualNode,'R')){
		//cout << "R" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0);
		pos[1]=actualNode->getPosPlayer(1)+1;
		
		int** boxes =moveBox(actualNode,pos,'R');
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getDepthTree()+1,actualNode->getPath().append("R"));
			nodes.push(node);
		}
	}	


	if(expand(actualNode,'L')){
		//cout << "L" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0);
		pos[1]=actualNode->getPosPlayer(1)-1;

		int** boxes =moveBox(actualNode,pos,'L');
		
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getDepthTree()+1,actualNode->getPath().append("L"));
			nodes.push(node);
		}
	}

	if(expand(actualNode,'D')){
		//cout << "D" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0)+1;
		pos[1]=actualNode->getPosPlayer(1);

		int** boxes =moveBox(actualNode,pos,'D');
		
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getDepthTree()+1,actualNode->getPath().append("D"));
			nodes.push(node);
		}
	}

	if(expand(actualNode,'U')){
		//cout << "U" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0)-1;
		pos[1]=actualNode->getPosPlayer(1);

		int** boxes =moveBox(actualNode,pos,'U');
		
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getDepthTree()+1,actualNode->getPath().append("U"));
			nodes.push(node);
		}
	}
		
}

bool IterativeDFSAgent::isSolve(){
	int counting = 0;
	
	for (int i = 0; i < numBoxes; i++){
		
		if(searchBox(targets[i][0],targets[i][1], nodes.top())){
			counting++;
		}
		
	}
		
	if(counting == numBoxes){
		return true;
	}else return false;
	
}



