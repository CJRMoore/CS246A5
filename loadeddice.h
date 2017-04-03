#ifndef LOADEDDICE_H
#define LOADEDDICE_H
#include "dice.h"

class LoadedDice: public Dice {
  public:
    void setSeed(unsigned int s) override {};
    int rollDice() override;

    ~LoadedDice() {};
};

#endif
