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
#include <iostream>
#include <string>

class Builder: public Observer{
    BuilderType colour;
    std::vector<int> resources;
    std::vector<std::shared_ptr<Dice> > theDice;
    std::shared_ptr<Dice> currDice;
    static std::vector<std::string> playerColours;

    bool rolled;
    unsigned int numPoints;
    std::vector<int> ownedAddresses;

  public:
    Builder(BuilderType colour);
    BuilderType getColour();

    bool isWon();
    int roll();

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    std::shared_ptr<AbstractAddress> buildAtAddress(std::shared_ptr<AbstractAddress> a);
    std::shared_ptr<AbstractAddress> upgradeAddress(std::shared_ptr<AbstractAddress> a);
    std::shared_ptr<AbstractPath> upgradePath(std::shared_ptr<AbstractPath> p);

    static void setColours(std::vector<std::string> C){ playerColours = C; };
    void resetResources();
    void setDice(bool whichDice);
    void resetTurn(){ rolled = false; };

    ~Builder() {};
    friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Builder> b);
};

#endif
