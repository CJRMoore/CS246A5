#ifndef ADDRESS_H
#define ADDRESS_H
#include "abstractaddress.h"
#include <vector>

class Address: public AbstractAddress {
    bool adjacent; //set by path

  public:
    Address(int index): AbstractAddress(index) {};

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    Info getInfo() const override;
    std::vector<int> upgradeRequirements() override;
};

#endif
