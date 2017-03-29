#include "gameboard.h"
#include "resources.h"
#include "builder.h"
#include "path.h"
#include "address.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void GameBoard::Init(string boardFile) {
    // Set up tiles and read tile layout from file
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

    // Set up addresses
    for (int a=0; a<54; a++) theAddresses.push_back(make_shared<Address>(a));

    // Set up paths
    for (int r=0; r<72; r++) thePaths.push_back(make_shared<Path>(r));

    // Set up address-path observer-subject relationships
    // Hard-coded because I don't want to learn graph theory
    ifstream apf("TileAddressRelationship.txt");
    while (getline(apf,line)){
        stringstream ss(line);
        int tile, ad1, ad2, ad3;
        ss >> tile >> ad1 >> ad2 >> ad3;
        theBoard[tile]->attach(theAddresses[ad1]);
        theBoard[tile]->attach(theAddresses[ad2]);
        theBoard[tile]->attach(theAddresses[ad3]);
    }
}

void GameBoard::moveGeese(int t){}

void GameBoard::save(string sFile) {}

void GameBoard::load(string lFile) {}
