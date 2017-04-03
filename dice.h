#ifndef DICE_H
#define DICE_H


class Dice {
  public:
    virtual void setSeed(unsigned int s) = 0;
    virtual int rollDice() = 0;
    virtual ~Dice() = 0;
};

inline Dice::~Dice() {};
#endif

