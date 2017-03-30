#ifndef ABSTRACTADDRESS_H
#define ABSTRACTADDRESS_H
#include "subject.h"
#include "observer.h"
#include "buildingtypes.h"

class Info;
class Builder;

class AbstractAddress: public Observer, public Subject {
  protected:
    const int index;
//    BuildingType building;

  public:
    AbstractAddress(int index): index(index) {};
    virtual std::vector<int> upgradeRequirements() = 0;
};

#endif
