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
IterativeDFSAgent* iterativeDFSAgent; 

// Initial variables.
vector<string> boardIn;
int* pos;
int** initBoxesPosIn;
//int search = 0;
int numBoxesIn;

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
			boardIn.push_back(text);
		}
	}
	myBoard.close();

	// The player's position is stored in the array variables.
	pos = new int[2];
	vector<string> playerPosition; 
    stringstream firstCheck(file[endBoard]);
    string med;
 	getline(firstCheck, med, ',');
    playerPosition.push_back(med); 
	getline(firstCheck, med, ',');
    playerPosition.push_back(med); 
	pos[0] = stoi(playerPosition[0]);
	pos[1] = stoi(playerPosition[1]);
	initBoxesPosIn = new int*[(file.size() - (endBoard))];
	int flag = 0;
	for (int i = (endBoard + 1); i < file.size(); i++) {
		initBoxesPosIn[flag] = new int[2];
		vector<string> boxPosition; 
    	stringstream check(file[i]);
    	string med;
    	while(getline(check, med, ',')) { 
        	boxPosition.push_back(med); 
    	} 
		initBoxesPosIn[flag][0] = stoi(boxPosition[0]);
		initBoxesPosIn[flag][1] = stoi(boxPosition[1]);
		flag++;
	}
	numBoxesIn = (file.size() - (endBoard + 1));
}

// Main method
int main(int argc, char** argv) {
	readFiles(argv[1]);

	// BFS
	agentBFS = new BFSAgent(numBoxesIn, pos, initBoxesPosIn, &boardIn);
	agentBFS -> identifyTargets();
	cout << "BFS: " << agentBFS -> startSearch() << endl;

	// DFS
	agentDFS = new DFSAgent(numBoxesIn, pos, initBoxesPosIn, &boardIn);
	agentDFS -> identifyTargets();
	cout << "DFS: "  << agentDFS -> startSearch() << endl;

	/* IterativeDFS (Review the methods here. Program overflows: @bryansbr, @AndresDFX).
	iterativeDFSAgent = new IterativeDFSAgent(numBoxesIn, pos, initBoxesPosIn, &boardIn);	
	iterativeDFSAgent -> identifyTargets();
	cout << "IterativeDFS: " << iterativeDFSAgent -> startSearch() << endl;*/
}