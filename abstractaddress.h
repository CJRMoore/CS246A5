#ifndef ABSTRACTADDRESS_H
#define ABSTRACTADDRESS_H
#include "subject.h"
#include "observer.h"
#include "buildingtypes.h"
#include "buildertype.h"
#include "resources.h"
#include "buildingtypes.h"

class Info;
class Builder;

class AbstractAddress: public Observer, public Subject {
  protected:
    const int index;
    BuilderType owner;
    ResourceType triggeredResource;

  public:
    AbstractAddress(int index): index(index), owner(BuilderType::None) {};
    virtual std::vector<int> upgradeRequirements(Builder &b) = 0;
    virtual int getIndex() { return index; };
    virtual int getResLevel()=0;

    virtual void setOwner(BuilderType o){ owner = o; };

    SubscriptionType subType() const override { return SubscriptionType::Tile; };
};

#endif
