#include "loadeddice.h"
#include <iostream>

using namespace std;

int LoadedDice::rollDice(){
    int v1, v2;
    cin >> v1 >> v2;
    if (v1<1 || v1>6 || v2<1 || v2>6){
        throw(string("Invalid roll."));
    }
    if (!cin.fail()) return v1+v2;
    else throw(string("INVALID_LOADED_DICE_ROLL"));
}
