#ifndef FAIRDICE_H
#define FAIRDICE_H
#include "dice.h"

class FairDice: public Dice {
  public:
    void setSeed(unsigned int s) override;
    int rollDice() override;
    ~FairDice() {};
};

#endif
