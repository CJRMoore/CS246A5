#include "subject.h"
#include "observer.h"
#include "subscriptions.h"

Subject::~Subject() {}

void Subject::attach(std::shared_ptr<Observer> o){
    observers.push_back(o);
}

void Subject::transfer(Subject *s){
    for (unsigned int i=0; i<observers.size(); i++){
        s->attach(observers[0]);
    }
}

void Subject::notifyObservers(SubscriptionType t){
    for (unsigned int i=0; i<observers.size(); i++){
        if ((observers[i]->subType()==t)) {
            observers[i]->notify(*this);
        }
    }
}
