#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "subscriptions.h"


class Info;
class Observer;

class Subject{
    std::vector<std::shared_ptr<Observer> > observers;
  public:
    void attach(std::shared_ptr<Observer> o);
    void notifyObservers(SubscriptionType t);
    virtual Info getInfo() const = 0;
    virtual ~Subject() = 0;
};
#endif
