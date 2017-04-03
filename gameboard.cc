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
#include <cstdlib>

using namespace std;

void GameBoard::reset(){
    theBoard.resize(0);
    theAddresses.resize(0);
    thePaths.resize(0);
}

void GameBoard::Init(string boardFile, vector<shared_ptr<Builder> > &thePlayers) {
    // Set up tiles and read tile layout from file
    // In principle, would work for expanded board size
    // Random board implemented below
    bool loadedFromFile = false;
    ifstream bf;
    if (boardFile!="") {
        bf.open(boardFile);
        if (!bf.fail()){ // boardFile is a file
            string line;
            int t=0;
            while (getline(bf,line)){ // input as either pairs or one line
                stringstream ss(line);
                int r, diceValue;
                while (!ss.eof()) {
                    ss >> r >> diceValue;
                    theBoard.push_back(make_shared<Tile>(r, t++, diceValue));
                }
            }
        }
        else{ // boardFile was not a layout file, but a string from a loaded file
            loadedFromFile = true;
            stringstream ss(boardFile);
            int r, diceValue, t=0;
            while (ss >> r >> diceValue){
                theBoard.push_back(make_shared<Tile>(r, t++, diceValue));
            }
        }
    }
    // Random board
    else{
        vector<int> res(3,4);
        res.push_back(3);
        res.push_back(3);
        res.push_back(1);

        for (int i=0; i<19; i++){
            int r = rand()%(res[0]+res[1]+res[2]+res[3]+res[4]+res[5]);
            int whichRes = -1;
            int gtlt=0;
            for (int j=0; j<res.size(); j++){
                gtlt += res[j];
                if (r < gtlt){
                    whichRes = j;
                    res[j]--;
                    break;
                }
            }
            theBoard.push_back(make_shared<Tile>(whichRes, i, rand()%6+1));
        }
    }


    // Set up addresses
    for (int a=0; a<54; a++) theAddresses.push_back(make_shared<Address>(a));

    // Set up paths
    for (int r=0; r<72; r++) thePaths.push_back(make_shared<Path>(r));

    // Set up address-tile observer-subject relationships
    // Hard-coded because I don't want to learn graph theory
    ifstream apf("TileAddressRelationship.txt");
    string line;
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

    // Set up adddress-path oberver-subect relationships
    ifstream atf("AddressPathRelationship.txt");
    while (getline(atf,line)){
        stringstream ss(line);
        int address, path;
        ss >> address;
        while (true){
            ss >> path;
            if (ss.fail()) break;
            theAddresses[address]->attach(thePaths[path]);
            thePaths[path]->attach(theAddresses[address]);
        }
    }

    // Set up players, then have them place their first residences
    theColours.push_back("Blue");
    theColours.push_back("Red");
    theColours.push_back("Orange");
    theColours.push_back("Yellow");
    Builder::setColours(theColours);

    vector<string> theResources;
    theResources.push_back("BRICK");
    theResources.push_back("Energy");
    theResources.push_back("GLASS");
    theResources.push_back("HEAT");
    theResources.push_back("WIFI");
    Builder::setResourceStr(theResources);

    if (!loadedFromFile){
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

string GameBoard::save(){
    stringstream ss;
    for (int i=0; i<theBoard.size(); i++) ss << int(theBoard[i]->getInfo().resource) << " " << theBoard[i]->getDiceValue() << " ";
    ss << endl;
    return ss.str();
}

void GameBoard::load(string lFile, vector<shared_ptr<Builder> > &thePlayers) {

}

void GameBoard::setSeed(unsigned int s){
    srand(s);
}
