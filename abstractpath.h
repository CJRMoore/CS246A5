#ifndef ABSTRACTPATH_H
#define ABSTRACTPATH_H
#include "subject.h"

class Builder;

class AbstractPath: public Subject {
    const int index;
    //virtual void buildRoad(Builder *b) = 0;

  public:
    AbstractPath(): index(-1) {};
    AbstractPath(int index): index(index) {};
    virtual bool hasRoad() const = 0;
    virtual int getIndex() { return index; };

};
#endif
