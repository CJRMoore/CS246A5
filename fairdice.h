#ifndef FAIRDICE_H
#define FAIRDICE_H
#include "dice.h"

class FairDice: public Dice {
  public:
    int rollDice() override;
    ~FairDice() {};
};

#endif
