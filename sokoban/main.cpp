/*

File name: main.cpp
Creation date: 02/11/2020
Modification date: 15/11/2020
Authors: Bryan Steven Biojó     - 1629366
         Julián Andrés Castaño  - 1625743
		 Juan Sebastián Saldaña - 
		 El otro men xd         - 

*/

// Libraries
#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include "Vertex.h"
#include "BFSAgent.h"
#include "DFSAgent.h"
#include "IterativeDFSAgent.h"
using namespace std;

// Creation objects.
BFSAgent* agentBFS; 
DFSAgent* agentDFS; 
IterativeDFSAgent* iterativeAgentDFS; 

// Initial variables.
vector<string> board;
int* pos;
int** initBoxesPos;
int search = 0;
int numBoxes;

// Reading files
void readFiles(string fileName) {
	ifstream myBoard(fileName);
	vector<string> file;
	int endBoard = 0;
	string text;
	while (!myBoard.eof()) {
		myBoard >> text;
		if (text[0]!= 'W' && text[0] != '0' && text[0] != 'X' && endBoard == 0) {
			endBoard = file.size();
		}		
		file.push_back(text);
		if (endBoard == 0) {
			board.push_back(text);
		}
	}
	myBoard.close();

	//Se almacena la posición del jugador en las variables de arreglo (REVISAR ESTO @bryansbr)
	pos = new int[2];
	vector <string> playerPosition; 
    stringstream firstCheck(file[endBoard]);
    string med;
 	getline(firstCheck, med, ',');
    playerPosition.push_back(med); 
	getline(firstCheck, med, ',');
    playerPosition.push_back(med); 
	pos[0] = stoi(playerPosition[0]);
	pos[1] = stoi(playerPosition[1]);
	initBoxesPos = new int*[(file.size() - (endBoard))];
	int flag = 0;
	for(int i = (endBoard + 1) ; i < file.size(); i++) {
		initBoxesPos[flag] = new int[2];
		vector <string> boxPosition; 
    	stringstream check(file[i]);
    	string med;
    	while(getline(check, med, ',')) { 
        	boxPosition.push_back(med); 
    	} 
		initBoxesPos[flag][0] = stoi(boxPosition[0]);
		initBoxesPos[flag][1] = stoi(boxPosition[1]);
		flag++;
	}
	numBoxes = (file.size() - (endBoard + 1));
}

// Main method
int main(int argc, char **argv) {
	readFiles(argv[1]);

	// BFS
	agentBFS = new BFSAgent(numBoxes, pos, initBoxesPos, &board);
	agentBFS -> identifyTargets();
	cout << "BFS: " << agentBFS -> startSearch() << endl;

	// DFS
	agentDFS = new DFSAgent(numBoxes, pos, initBoxesPos, &board);
	agentDFS -> identifyTargets();
	cout << "DFS: "  << agentDFS -> startSearch() << endl;

	/* IterativeDFS
	iterativeAgentDFS = new IterativeDFSAgent(numBoxes, pos, initBoxesPos, &board);	
	iterativeAgentDFS -> identifyTargets();
	cout << "IterativeDFS: " << iterativeAgentDFS -> startSearch() << endl;*/
}