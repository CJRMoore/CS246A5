#ifndef ADDRESS_H
#define ADDRESS_H
#include "abstractaddress.h"
#include "buildertype.h"
#include <vector>

class Builder;

class Address: public AbstractAddress {
    bool adjacent; //set by path

  public:
    Address(int index): AbstractAddress(index) {};
    Address(const Address &other): AbstractAddress(other.index) {};

    void notify(Subject &whoNotified) override;
    int getResLevel() override { return 0; };

    Info getInfo() const override;
    std::vector<int> upgradeRequirements(Builder &b) override;
};

#endif
