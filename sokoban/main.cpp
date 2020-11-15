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
int* posIn;
int** initBoxesPos;
int search = 0;
int numBoxes;

// Reading files
void readFiles(string fileName) {
	ifstream myBoard(fileName);
	vector<string> file;
	int endBoard = 0;
	string text;

// Check do while loops in algorithms...	
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
	posIn = new int[2];
	vector <string> posicionJu; 
    stringstream check1(file[endBoard]);
    string intermediate;
 	getline(check1, intermediate, ',');
    posicionJu.push_back(intermediate); 
	getline(check1, intermediate, ',');
    posicionJu.push_back(intermediate); 
	posIn[0] = stoi(posicionJu[0]);
	posIn[1] = stoi(posicionJu[1]);
	initBoxesPos = new int*[(file.size() - (endBoard))];
	int flag = 0;
	for(int i = (endBoard + 1) ; i < file.size(); i++) {
		initBoxesPos[flag] = new int[2];
		vector <string> posicionCa; 
    	stringstream check(file[i]);
    	string intermediate;
    	while(getline(check, intermediate, ',')) { 
        	posicionCa.push_back(intermediate); 
    	} 
		initBoxesPos[flag][0] = stoi(posicionCa[0]);
		initBoxesPos[flag][1] = stoi(posicionCa[1]);
		flag++;
	}
	numBoxes = (file.size() - (endBoard + 1));
}

// Main method
int main(int argc, char **argv) {
	readFiles(argv[1]);

	// BFS
	agentBFS = new BFSAgent(numBoxes, posIn, initBoxesPos, &board);
	agentBFS -> identifyTargets();
	cout << "BFS: " << agentBFS -> startSearch() << endl;

	// DFS
	agentDFS = new DFSAgent(numBoxes, posIn, initBoxesPos, &board);
	agentDFS -> identifyTargets();
	cout << "DFS: "  << agentDFS -> startSearch() << endl;

	// IterativeDFS
	iterativeAgentDFS = new IterativeDFSAgent(numBoxes, posIn, initBoxesPos, &board);	
	iterativeAgentDFS -> identifyTargets();
	cout << "IterativeDFS: " << iterativeAgentDFS -> startSearch() << endl;
	//return 0;
}