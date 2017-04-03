#ifndef HOUSE_H
#define HOUSE_H
#include "subject.h"
#include "observer.h"
#include "residence.h"
#include <memory>

class Info;

class House: public Residence {
  public:
    House(std::shared_ptr<AbstractAddress> aa);
//    void upgrade();

    Info getInfo() const override;

    void notify(Subject &whoNotified) override;

    std::vector<int> upgradeRequirements(Builder &b) override;

    int getIndex() override { return aa->getIndex(); };
    int getResLevel() override { return 2; };

    void setOwner(BuilderType o) override { aa->setOwner(o); }
};

#endif
