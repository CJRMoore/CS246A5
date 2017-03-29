#ifndef OBSERVER_H
#define OBSERVER_H

#include "subscriptions.h"

class Subject;
class Tile;

class Observer{
  public:
    virtual void notify(Subject &whoNotified) = 0;
    virtual SubscriptionType subType() const =  0;
    virtual ~Observer() = default;
};

#endif
