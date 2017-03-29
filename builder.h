#ifndef BUILDER_H
#define BUILDER_H
#include "observer.h"
#include "buildertype.h"
#include <vector>
#include <memory>

class Dice;
class Path;
class Residence;
class Address;

class Builder: public Observer{
    BuilderType colour;
    std::vector<int> resources;
    std::vector<std::unique_ptr<Dice> > theDice;

  public:
    Builder(BuilderType colour);
    BuilderType getColour();
    void buildResidence(Address *a);
    void buildPath(Path *p);
    void upgradeResidence(Residence *r);

    bool isWon();
    int roll();
};

#endif
