#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "subscriptions.h"


class Info;
class Observer;

class Subject{
    std::vector<Observer*> observers;
  public:
    void attach(Observer *o);
    void notifyObservers(SubscriptionType t);
    virtual Info getInfo() const = 0;
    virtual ~Subject() = 0;
};
#endif