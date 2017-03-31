#include <iostream>
#include <string>
#include <memory>
#include "builder.h"
#include "buildertype.h"
#include "gameboard.h"
#include "resources.h"
using namespace std;

int main() {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd, aux;
    GameBoard g;
    vector<shared_ptr<Builder> > thePlayers;
    int turnCounter = 0;

    for (int i=0; i<4; i++){
        thePlayers.push_back(make_unique<Builder>(BuilderType(i)));
    }

    try {
    // Set up players and board
        g.Init("layout.txt", thePlayers);
        shared_ptr<Builder> currPlayer;
        thePlayers[0]->resetResources();

        while (true) {
            currPlayer = thePlayers[turnCounter];
            cout << "Builder " << g.getColours()[turnCounter] << "'s turn." << endl;
            cout << currPlayer;

            while (true){
                cin >> cmd;
            
                try{
                    if (cmd == "loaded"){ currPlayer->setDice(0); }
                    else if (cmd == "fair"){ currPlayer->setDice(1); }
                    else if (cmd == "roll"){ 
                        g.distributeResources(currPlayer->roll()); 
                    }
                    else if (cmd == "board"){}
                    else if (cmd == "status"){ cout << currPlayer; }
                    else if (cmd == "residences"){}
                    else if (cmd == "build-road"){ 
                        int path;
                        cin >> path;
                        g.buildRoad(currPlayer, path);
                    }
                    else if (cmd == "build-res"){
                        int res;
                        cin >> res;
                        g.buildResidence(currPlayer, res);
                    }
                    else if (cmd == "improve"){}
                    else if (cmd == "trade"){}
                    else if (cmd == "save"){}
                    else if (cmd == "help"){}
                    else if (cmd == "next"){
                        turnCounter = (turnCounter+1)%4;
                        break;
                    }
                }
                catch(string s){
                    cout << s << endl;
                }
            }
            for (unsigned int i=0; i<thePlayers.size(); i++) thePlayers[i]->resetTurn();
        }
    }
    catch (ios::failure &) {
    }
}
