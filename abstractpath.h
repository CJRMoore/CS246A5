#ifndef ABSTRACTPATH_H
#define ABSTRACTPATH_H
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
#include "buildertype.h"

class Builder;

class AbstractPath: public Subject, public Observer {
  protected:
    const int index;
    BuilderType owner;
    bool tripped;

  public:
    AbstractPath(): index(-1), owner(BuilderType::None), tripped(false) {};
    AbstractPath(int index): index(index), owner(BuilderType::None), tripped(false) {};
    virtual bool hasRoad() const = 0;
    virtual int getIndex() { return index; };

    virtual std::vector<int> upgradeRequirements(Builder &b) = 0;
    virtual void setOwner(BuilderType o) { owner = o; };

    SubscriptionType subType() const override { return SubscriptionType::Path; };
};
#endif
