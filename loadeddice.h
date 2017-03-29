#ifndef LOADEDDICE_H
#define LOADEDDICE_H
#include "dice.h"

class LoadedDice: public Dice {
  public:
    int rollDice() override;

    ~LoadedDice() {};
};

#endif
