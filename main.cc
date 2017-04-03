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

void help(){
    cout << "=============================" << endl
         << "== Welcome to Constructor! ==" << endl
         << "=============================" << endl << endl
         << "This is a game is based on the popular board game, Settlers of Catan, but adapted to the University of Waterloo campus.  For game insstructions, please see Settlers of Catan rules." << endl << endl
         << "Valid moves at beginning of turn:" << endl
         << "\tloaded:\tSet dice to loaded (player chooses dice roll between 2 and 12).  \n\t\tAt beginning of game, all players have loaded dice." << endl
         << "\tfair:\tSet dice to fair.  Two dice are randomly rolled." << endl
         << "\troll:\tRoll chosen dice." << endl << endl
         << "Valid moves after rolling:" << endl
         << "\tboard:\tPrint the board to the command line." << endl
         << "\tstatus:\tPrint player points and resources." << endl
         << "\tresidences:\tPrint the address and type of residence owned by the player." << endl
         << "\thelp:\tPrint this help message." << endl
         << "\tnext:\tfinish turn" << endl
         << "\tbuild-road <road#>:\tBuild road at the number given.\n\t\t\t\tPlayer must have enough resources, and path must not be owned." << endl
         << "\tbuild-res <address>:\tBuild residence at address given.  \n\t\t\t\tPlayer must have enough resoures, and address must not\n\t\t\t\thave a residence already built." << endl
         << "\timprove <address>:\tImprove residence.  Player must have enough resources, \n\t\t\t\tand residence must have been built." << endl
         << "\ttrade <player> <give> <take>:\tTrade with other player, and give one resource\n\t\t\t\t\tto take one resource." << endl
         << "\tsave <file>:\tSave game to file. Load later from command line." << endl; 
}

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
        //thePlayers[0]->resetResources();

        // ------- Begin/resume game -------
        bool done = false;
        while (!done) {
            currPlayer = thePlayers[turnCounter];
            cout << "Builder " << g.getColours()[turnCounter] << "'s turn." << endl;
            cout << currPlayer;

            // Make player roll dice
            bool rolled = false;
            while (!rolled){
                cin >> cmd;
                // Set dice to loaded
                if (cmd == "loaded"){
                    cout << "Dice set to loaded." << endl;
                    currPlayer->setDice(0);
                }
                // Set dice to fair
                else if (cmd == "fair"){
                    cout << "Dice set to fair." << endl;
                    currPlayer->setDice(1);
                }
                // Roll dice
                else if (cmd == "roll"){
                    g.distributeResources(currPlayer->roll());
                    for (int i=0; i<thePlayers.size(); i++) thePlayers[i]->printTurnGains();
                    rolled = true;
                }  
                else if (cmd == "help"){
                    help();
                }
                else{
                    cout << "Invalid action; currently valid actions are 'loaded', 'fair', and 'roll'" << endl;
                }
            }
            while (true){
                cin >> cmd;
                try{
                    // Set dice to loaded
                    if (cmd == "loaded"){
                        cout << "Dice set to loaded." << endl;
                        currPlayer->setDice(0); 
                    }
                    // Set dice to fair
                    else if (cmd == "fair"){ 
                        cout << "Dice set to fair." << endl;
                        currPlayer->setDice(1); 
                    }
                    // Roll dice
                    else if (cmd == "roll"){
                        cout << "Already rolled." << endl;
                    }
                    else if (cmd == "board"){ // Print board (TO BE IMPLEMENTED
                    }
                    // Print status of plyer
                    else if (cmd == "status"){ 
                        cout << currPlayer; 
                    }
                    // Print player's residences
                    else if (cmd == "residences"){
                        cout << g.getColours()[turnCounter] << " has built:" << endl 
                             << currPlayer->listOwnedResidences();
                    }
                    // Build road on unused path
                    else if (cmd == "build-road"){
                        int path;
                        cin >> path;
                        g.buildRoad(currPlayer, path);
                    }
                    // Build residence at unused address
                    else if (cmd == "build-res"){
                        int res;
                        cin >> res;
                        g.buildResidence(currPlayer, res);
                    }
                    // Improve existing residence located at address
                    else if (cmd == "improve"){
                        int res;
                        cin >> res;
                        g.upgradeResidence(currPlayer, res);
                    }
                    else if (cmd == "trade"){} // Trade with other player
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
                    // Print help text
                    else if (cmd == "help"){
                        help();
                    }
                    // Finish turn
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
            // Check if any player won
            bool hasWon = false;
            for (int i=0; i<thePlayers.size(); i++){
                if (thePlayers[i]->isWon()){
                    cout << "Player " << g.getColours()[i] << " has won with " << thePlayers[i]->getNumPoints() << " points!" << endl
                    << "Would you like to play again? [y/n]" << endl;
                    string ans;
                    cin >> ans;
                    // End game
                    if (ans == "n" || ans == "N"){
                        done = true;
                    }
                    // Restart game
                    else if (ans == "y" || ans == "Y"){
                        thePlayers.resize(0);
                        for (int i=0; i<4; i++) {
                            thePlayers.push_back(make_unique<Builder>(BuilderType(i)));
                            if (seedSet) thePlayers.back()->setSeed(seed);
                        }
                        stringstream ss;
                        ss << g.save();
                        g.reset();
                        g.Init(ss.str(), thePlayers);
                    }
                    else{
                        cout << "Unknown answer." << endl;
                        cout << "Would you like to play again? [y/n]" << endl;
                    }
                }
            }

        }
    }
    catch (ios::failure &) {
    }
}
