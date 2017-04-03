#ifndef BUILDER_H
#define BUILDER_H
#include "observer.h"
#include "buildertype.h"
#include "residence.h"
#include "path.h"
#include "abstractaddress.h"
#include "dice.h"
#include "gameboard.h"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>

class GameBoard;

class Builder: public Observer{
    BuilderType colour;
    std::vector<int> resources;
    std::vector<int> turnGains;

    std::vector<std::shared_ptr<Dice> > theDice;
    std::shared_ptr<Dice> currDice;
    static std::vector<std::string> playerColours;
    static std::vector<std::string> resourceStr;

    bool rolled;
    unsigned int numPoints;
    std::vector<std::shared_ptr<AbstractAddress> > ownedAddresses;
    std::vector<std::shared_ptr<AbstractPath> > ownedRoads;

  public:
    Builder(BuilderType colour);
    BuilderType getColour();

    bool isWon();
    int roll();
    void setSeed(unsigned int s){ theDice[1]->setSeed(s); };

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    std::shared_ptr<AbstractAddress> buildAtAddress(std::shared_ptr<AbstractAddress> a);
    std::shared_ptr<AbstractAddress> upgradeAddress(std::shared_ptr<AbstractAddress> a);
    std::shared_ptr<AbstractPath> upgradePath(std::shared_ptr<AbstractPath> p);

    static void setColours(std::vector<std::string> C){ playerColours = C; };
    static void setResourceStr(std::vector<std::string> C){ resourceStr = C; };
    void resetResources();
    void setResources(std::vector<int> r){ resources = r; };
    void setDice(bool whichDice);
    void resetTurn(){ rolled = false; };
    void printTurnGains();

    std::string listOwnedResidences();

    void restorePlayerStats(GameBoard &g, std::string &s);

    ~Builder() {};
    friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Builder> b);
    friend std::ofstream &operator<<(std::ofstream &out, const std::shared_ptr<Builder> b);
};

#endif
