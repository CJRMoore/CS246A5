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
    std::vector<std::unique_ptr<Dice> > theDice;

  public:
    Builder(BuilderType colour);
    BuilderType getColour();
    bool buildableAddress(std::shared_ptr<AbstractAddress> a);
    void buildRoad(std::shared_ptr<Path> p);
    void upgradeResidence(std::shared_ptr<Residence> r);

    bool isWon();
    int roll(bool whichDice);

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    ~Builder() {};
};

#endif
