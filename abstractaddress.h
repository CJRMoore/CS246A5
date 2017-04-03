#ifndef ABSTRACTADDRESS_H
#define ABSTRACTADDRESS_H
#include "subject.h"
#include "observer.h"
#include "buildingtypes.h"
#include "buildertype.h"
#include "resources.h"
#include "info.h"
#include "buildingtypes.h"

class Builder;

class AbstractAddress: public Observer, public Subject {
  protected:
    const int index;
    BuilderType owner;
    ResourceType triggeredResource;

  public:
    AbstractAddress(int index): index(index), owner(BuilderType::None) {};
    AbstractAddress(int index, BuilderType owner): index(index), owner(owner) {};

    AbstractAddress(const AbstractAddress &other): index(other.index), owner(other.owner), triggeredResource(other.triggeredResource) {};
    AbstractAddress(AbstractAddress &&other): index(other.index), owner(other.owner),  triggeredResource(other.triggeredResource) {};

    // No copy assignment operator for classes with constant members
    /*AbstractAddress &operator=(AbstractAddress &other){
        this->index = other.getIndex();
        this->owner = other.getOwner();
        this->triggeredResource = other.getInfo().resource;
        return *this;
    };*/
    AbstractAddress &operator=(AbstractAddress &&other){
        this->index = other.getIndex();
        this->owner = other.getOwner();
        this->triggeredResource = other.triggeredResource;
        return *this;
    };

    virtual std::vector<int> upgradeRequirements(Builder &b) = 0;
    virtual int getIndex() { return index; };
    virtual int getResLevel()=0;

    virtual void setOwner(BuilderType o){ owner = o; };
    BuilderType getOwner(){ return owner; };

    SubscriptionType subType() const override { return SubscriptionType::Tile; };
};

#endif
