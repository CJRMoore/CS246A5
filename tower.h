#ifndef TOWER_H
#define TOWER_H
#include "subject.h"
#include "observer.h"
#include "residence.h"
#include <memory>

class Info;

class Tower: public Residence {
  public:
    Tower(std::shared_ptr<AbstractAddress> aa);
//    void upgrade();

    Info getInfo() const override;

    void notify(Subject &whoNotified) override;

    std::vector<int> upgradeRequirements(Builder &b) override;
    int getIndex() override { return aa->getIndex(); };
    int getResLevel() override { return 3; };

    void setOwner(BuilderType o) override { aa->setOwner(o); }
};

#endif
