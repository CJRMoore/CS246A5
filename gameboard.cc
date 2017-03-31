#include "gameboard.h"
#include "resources.h"
#include "builder.h"
#include "path.h"
#include "road.h"
#include "address.h"
#include "basement.h"


#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void GameBoard::Init(string boardFile, vector<shared_ptr<Builder> > &thePlayers) {
    // Set up tiles and read tile layout from file
    ifstream bf(boardFile);
    string line;
    int t=0;
    while (getline(bf,line)){ // input as either pairs or one line
        stringstream ss(line);
        int r;
        int dV;
        while (!ss.eof()) {
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
        theBoard[tile]->attach(theAddresses[ad1+1]);
        theBoard[tile]->attach(theAddresses[ad2]);
        theBoard[tile]->attach(theAddresses[ad2+1]);
        theBoard[tile]->attach(theAddresses[ad3]);
        theBoard[tile]->attach(theAddresses[ad3+1]);
    }

    // Set up players, then have them place their first residences
    theColours.push_back("Blue");
    theColours.push_back("Red");
    theColours.push_back("Orange");
    theColours.push_back("Yellow");
    Builder::setColours(theColours);

    for (int p = int(BuilderType::Blue); p <= int(BuilderType::Yellow); p++) {
        bool done = false;
        unsigned int pAddress;
        while (!done){
            cout << "Builder " << theColours[int(thePlayers[p]->getColour())] << ", where do you want to build a basement?" << endl;
            cin >> pAddress;
            if (pAddress >=0 && pAddress < theAddresses.size()) done = true;
            else {
                cout << "Invalid address (must be in range [0," << (theAddresses.size()-1) << "]); try again" << endl;
            }
        }
        theAddresses[pAddress] = thePlayers[p]->buildAtAddress(theAddresses[pAddress]);
        theAddresses[pAddress]->attach(thePlayers[p]);
        thePlayers[p]->resetResources();
    }
}


void GameBoard::buildRoad(shared_ptr<Builder> &b, int index){
    if (index >= thePaths.size()) throw(string("Invalid path."));
    thePaths[index] = b->upgradePath(thePaths[index]);
}

void GameBoard::buildResidence(shared_ptr<Builder> &b, int index){
    if (index >= theAddresses.size()) throw(string("Invalid address."));
    theAddresses[index] = b->buildAtAddress(theAddresses[index]);
    theAddresses[index]->attach(b);
}

void GameBoard::upgradeResidence(shared_ptr<Builder> &b, int index){
    if (index >= theAddresses.size()) throw(string("Invalid address."));
    theAddresses[index] = b->upgradeAddress(theAddresses[index]);
    theAddresses[index]->attach(b);
}



void GameBoard::distributeResources(int r){
    for (unsigned int i=0; i<theBoard.size(); i++){
        if (theBoard[i]->getDiceValue() == r) {
            theBoard[i]->notifyObservers(SubscriptionType::Tile);
        }
    }
}


void GameBoard::moveGeese(int t){}

void GameBoard::save(string sFile) {}

void GameBoard::load(string lFile) {}
