#include "loadeddice.h"
#include <iostream>

using namespace std;

int LoadedDice::rollDice(){
    int v1;
    cout << "Input a roll between 2 and 12: " << endl;
    cin >> v1;
    if (v1<2 || v1>12){
        throw(string("Invalid roll."));
    }
    if (!cin.fail()) return v1;
    else throw(string("INVALID_LOADED_DICE_ROLL"));
}
