#ifndef RESIDENCE_H
#define RESIDENCE_H
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "abstractaddress.h"
#include <memory>
#include <vector>


class Residence: public AbstractAddress {
  protected:
    std::shared_ptr<AbstractAddress> aa;
    Info triggeredInfo;

  public:
    Residence(std::shared_ptr<AbstractAddress> aa, int index);
    virtual std::vector<int> upgradeRequirements() = 0;
//    void upgrade();

    //void notify(Subject &whoNotified) override;
    //SubscriptionType subType() const override;
};

#endif
