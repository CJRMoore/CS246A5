#ifndef BUILDER_H
#define BUILDER_H
#include "observer.h"
#include "buildertype.h"
#include "residence.h"
#include "path.h"
#include "abstractaddress.h"
#include "dice.h"
#include <vector>
#include <memory>


class Builder: public Observer{
    BuilderType colour;
    std::vector<int> resources;
    std::vector<std::shared_ptr<Dice> > theDice;
    std::shared_ptr<Dice> currDice;

  public:
    Builder(BuilderType colour);
    BuilderType getColour();
    bool upgradeAddress(std::shared_ptr<AbstractAddress> a);
    bool upgradePath(std::shared_ptr<Path> p);

    bool isWon();
    int roll(bool whichDice);

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    ~Builder() {};
};

#endif
