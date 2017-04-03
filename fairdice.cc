#include "fairdice.h"
#include <cstdlib>

int FairDice::rollDice(){
    return (rand()%6) + (rand()%6) + 2;
}

void FairDice::setSeed(unsigned int s){
    srand(s);
}
