#ifndef ADDRESS_H
#define ADDRESS_H
#include "abstractaddress.h"

class Address: public AbstractAddress {
  public:
    Address(int index): AbstractAddress(index) {};

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    Info getInfo() const override;
};

#endif
