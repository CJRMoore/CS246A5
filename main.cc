#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include "builder.h"
#include "buildertype.h"
#include "gameboard.h"
#include "resources.h"
using namespace std;

int main(int argc, char** argv) {
    // parse command line options
    bool seedSet = false;
    unsigned int seed;
    bool randomBoard = false;
    string loadFromFile("");
    string boardFromFile("layout.txt");

    for (int i=1; i<argc; i++){
        // Get random seed from command line
        if (string(argv[i])=="-seed"){
            stringstream ss;
            ss << argv[i+1];
            ss >> seed;
            seedSet = true;
            i++;
        }
        // Get saved file from command line
        else if (string(argv[i])=="-load"){
            if (boardFromFile!="layout.txt") cout << "-load argument called; ignoring -board" << endl;
            if (randomBoard) cout << "-load passed; ignoring -random-board." << endl;
            // rudimentary file check
            loadFromFile = string(argv[i+1]);
            ifstream f(loadFromFile);
            if (f.fail()){
                cout << "Error loading file " << loadFromFile << endl;
                return -1;
            }
            randomBoard = false;
            i++;
        }
        // Get board layout file from command line
        else if (string(argv[i])=="-board"){
            if (loadFromFile!="") cout << "-load argument already called; ignoring -board." << endl;
            if (randomBoard) cout << "-board passed; ignoring -random-board." << endl;
            // Rudimentary check for existence of file
            boardFromFile = argv[i+1];
            ifstream f(boardFromFile);
            if (f.fail()){
                cout << "Error loading file " << boardFromFile << endl;
                return -1;
            }
            randomBoard = false;
            i++;
        }
        // Check if random will be overridden by other arguments, then sets random boolean
        else if (string(argv[i])=="-random-board"){
            if (loadFromFile!="" || boardFromFile!="layout.txt") {
                cout << "Conflicting arguments (-random-board after -load or -board). Ignoring -random" << endl;
                continue;
            }
            randomBoard = true;
        }       
        // Print usage
        else {
            if (string(argv[i])!="help" && string(argv[i])!="-help") cout << "Unknown argument: " << argv[i] << endl;
            cout << "Usage: Constructor [-seed integer] [-load saveFile] [-board boardFile] [-random-board] [help]" << endl;
            cout << "\t-seed requires unsigned integer." << endl;
            cout << "\t-load requires a save file from a previously saved game." << endl;
            cout << "\t-board requires a properly formatted layout file. Default: layout.txt" << endl;
            cout << "\t-random-seed randomizes the board." << endl;
            cout << "\t help shows this message." << endl;
            return -1;
        }
    }

    // Initialize game board
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd, aux;
    GameBoard g;
    vector<shared_ptr<Builder> > thePlayers;
    int turnCounter = 0;

    // Initialize players
    for (int i=0; i<4; i++) {
        thePlayers.push_back(make_unique<Builder>(BuilderType(i)));
        if (seedSet) thePlayers.back()->setSeed(seed);
    }

    try {
        // Set up players and board
        if (seedSet) g.setSeed(seed);

        if (!randomBoard && loadFromFile=="") g.Init(boardFromFile, thePlayers);
        else if (randomBoard) g.Init("",thePlayers);
        // Load player data from file
        else if (loadFromFile!="") {
            ifstream f(loadFromFile);
            try {
                f >> turnCounter;
                vector<string> playerStats(4,"");
                getline(f,playerStats[0]); // get rid of turn counter line
                for (int line=0; line<4; line++) getline(f,playerStats[line]);
                getline(f,loadFromFile);
                g.Init(loadFromFile, thePlayers);
                for (int line=0; line<4; line++) thePlayers[line]->restorePlayerStats(g, playerStats[line]);
                cout << "Game successfully loaded from file." << endl;
            }
            catch(ios::failure &){
                cout << "Could not read from loaded file " << loadFromFile << "." << endl;
                return -1;
            }
        }
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
                        cout << endl;
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
