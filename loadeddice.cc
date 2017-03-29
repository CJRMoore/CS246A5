#include "loadeddice.h"
#include <iostream>

using namespace std;

int LoadedDice::rollDice(){
    int v1, v2;
    cin >> v1 >> v2;
    if (!cin.fail()) return v1+v2;
    else throw("INVALID_LOADED_DICE_ROLL");
}
