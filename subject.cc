#include "subject.h"
#include "observer.h"
#include "subscriptions.h"

Subject::~Subject() {}

void Subject::attach(std::shared_ptr<Observer> o){
    observers.push_back(o);
}

void Subject::notifyObservers(SubscriptionType t){
    for (unsigned int i=0; i<observers.size(); i++){
        if ((observers[i]->subType()==t)) observers[i]->notify(*this);
    }
}
