#ifndef BASEMENT_H
#define BASEMENT_H
#include "subject.h"
#include "observer.h"
#include "residence.h"
#include <memory>
#include <vector>

class Info;

class Basement: public Residence {
  public:
    Basement(std::shared_ptr<AbstractAddress> aa);
//    void upgrade();

    Info getInfo() const override;

    void notify(Subject &whoNotified) override;

    std::vector<int> upgradeRequirements(Builder &b) override;
    int getIndex() override { return aa->getIndex(); };
    int getResLevel() override { return 1; };

    void setOwner(BuilderType o) override { aa->setOwner(o); };
};

#endif
