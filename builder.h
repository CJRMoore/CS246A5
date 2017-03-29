#ifndef BUILDER_H
#define BUILDER_H
#include "observer.h"
#include "buildertype.h"
#include "dice.h"
#include <vector>
#include <memory>

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
    void buildRoad(Path *p);
    void upgradeResidence(Residence *r);

    bool isWon();
    int roll(bool whichDice);

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    ~Builder() {};
};

#endif
