#ifndef ABSTRACTPATH_H
#define ABSTRACTPATH_H
#include "subject.h"
#include "buildertype.h"

class Builder;

class AbstractPath: public Subject {
  protected:
    const int index;
    BuilderType owner;

  public:
    AbstractPath(): index(-1), owner(BuilderType::None) {};
    AbstractPath(int index): index(index), owner(BuilderType::None) {};
    virtual bool hasRoad() const = 0;
    virtual int getIndex() { return index; };

    virtual std::vector<int> upgradeRequirements(Builder &b) = 0;
    virtual void setOwner(BuilderType o) { owner = o; };
};
#endif
