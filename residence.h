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

  public:
    Residence(std::shared_ptr<AbstractAddress> aa): AbstractAddress(aa->getIndex()), aa(aa) {};
    int getIndex() override { return aa->getIndex(); };

    void setOwner(BuilderType o) override { aa->setOwner(o); };
//    void upgrade();

    //void notify(Subject &whoNotified) override;
    //SubscriptionType subType() const override;
};

#endif
