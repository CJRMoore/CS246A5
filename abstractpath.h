#ifndef ABSTRACTPATH_H
#define ABSTRACTPATH_H
#include "subject.h"

class Builder;

class AbstractPath: public Subject {
  protected:
    const int index;

  public:
    AbstractPath(): index(-1) {};
    AbstractPath(int index): index(index) {};
    virtual bool hasRoad() const = 0;
    virtual int getIndex() { return index; };

    virtual std::vector<int> upgradeRequirements() = 0;
};
#endif
