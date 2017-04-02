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

        bool done = false;
        while (!done) {
            currPlayer = thePlayers[turnCounter];
            cout << "Builder " << g.getColours()[turnCounter] << "'s turn." << endl;
            cout << currPlayer;

            while (true){
                cin >> cmd;
            
                try{
                    if (cmd == "loaded"){ 
                        cout << "Dice set to loaded." << endl;
                        currPlayer->setDice(0); 
                    }
                    else if (cmd == "fair"){ 
                        cout << "Dice set to fair." << endl;
                        currPlayer->setDice(1); 
                    }
                    else if (cmd == "roll"){ 
                        g.distributeResources(currPlayer->roll()); 
                        for (int i=0; i<thePlayers.size(); i++) thePlayers[i]->printTurnGains();
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
                    else if (cmd == "improve"){
                        int res;
                        cin >> res;
                        g.upgradeResidence(currPlayer, res);
                    }
                    else if (cmd == "trade"){}
                    // Save game to file
                    else if (cmd == "save"){
                        string sFile;
                        cin >> sFile;
                        ofstream f(sFile);
                        f << turnCounter << endl;
                        for (int i=0; i<thePlayers.size(); i++) f << thePlayers[i];
                        f << g.save();
                        f.close(); // I  know it's not necessary, but ofstream is not no-throw
                        cout << "Succesfully saved to file " << sFile << ".  Continue? [y/n]" << endl; 
                        string cont;
                        cin >> cont;
                        if (cont=="n" || cont=="N"){
                            done = true;
                            break;
                        }
                    }
                    else if (cmd == "help"){}
                    else if (cmd == "next"){
                        turnCounter = (turnCounter+1)%4;
                        break;
                    }
                    else if (cmd == "cheat"){
                        cout << "THIS IS FOR DEBUGGING PURPOSES! Enable? [y/n]" << endl;
                        string in;
                        cin >> in;
                        if (in == "y" || in == "Y"){
                            currPlayer->setResources(vector<int>(5,99));
                            cout << "Cheats enabled" << endl;
                        }
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
