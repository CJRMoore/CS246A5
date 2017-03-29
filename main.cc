#include <iostream>
#include <string>
#include "gmeboard.h"
using namespace std;

int main() {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd, aux;
  GameBoard g;
  int moves = 0;

  // You will need to make changes to this code.

  try {
    //bool gameState = false;
    //bool boardReady = false;

    while (true) {
      cin >> cmd;

      // New game board
      /*if (cmd == "new") {
        int n;
        cin >> n;
        g.init(n);
        gameState = false;
      }
      // Enter initialization state of game board
      else if (cmd == "init") {
        bool done = false;
        while (!done){
            int r, c;
            cin >> r >> c;
            if (r==-1 && c==-1) {
                done=true;
                break;
            }
            else if (r<0 || c<0){ // for safety
                continue;
            }
            g.turnOn(r,c);
        }
        cout << g;
        boardReady = true;
      }
      // Start a new game
      else if (cmd == "game") {
        if (!boardReady) {
            cerr << "Board not initialized" << endl;
            continue;
        }
        cin >> moves;
        gameState = true;
      }

      // toggle cells
      else if (cmd == "switch") {
        //if ((moves>0)){
           int r = 0, c = 0;
            cin >> r >> c;
            g.toggle(r,c);
            cout << g;
            moves--;
        //}
        //else {
        //    cerr << "Out of moves" << endl;
        //}
      }
      
      if (gameState) cout << moves << (moves==1?" move left":" moves left") << endl;
      // Report game state, moves left
      if (moves==0 && gameState){
        gameState = false;
        cout << (g.isWon()?"Won":"Lost") << endl;
        break;
      }
      if (moves<0) moves=0;*/
    }
  }
  catch (ios::failure &) {
  }
}
