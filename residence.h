#ifndef RESIDENCE_H
#define RESIDENCE_H
#include "subject.h"
#include "observer.h"
#include "abstractaddress.h"
#include <memory>

class Info;

class Residence: public AbstractAddress {
    AbstractAddress *aa;
    int upgradeProgress;

  public:
    Residence(AbstractAddress *aa, int index);
    void upgrade();

    Info getInfo() const override;

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;
};

#endif
