#ifndef ABSTRACTPATH_H
#define ABSTRACTPATH_H
#include "subject.h"

class Builder;

class AbstractPath: public Subject {
    const int index;
    //virtual void buildRoad(Builder *b) = 0;

  public:
    virtual bool hasRoad() const = 0;
    Info getInfo() const override;

    virtual ~AbstractPath() = 0;
};

AbstractRoat::~AbstractRoad() {};
#endif
