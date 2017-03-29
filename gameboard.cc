#include "gameboard.h"
#include "resources.h"
#include "builder.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void GameBoard::Init(string boardFile) {
    theBoard.resize(0);

    ifstream bf(boardFile);
    string line;
    int t=0;
    while (getline(bf,line)){ // input as either pairs or one line
        stringstream ss(line);
        int r;
        int dV;
        while (!ss.fail()) {
            ss >> r >> dV;
            theBoard.push_back(make_shared<Tile>(r, t++, dV));
        }
    }

//    theAddresses.resize
}

void GameBoard::moveGeese(int t){}

void GameBoard::save(string sFile) {}

void GameBoard::load(string lFile) {}
