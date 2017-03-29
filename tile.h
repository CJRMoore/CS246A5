#ifndef TILE_H
#define TILE_H
#include "resources.h"
#include "subscriptions.h"
#include "observer.h"
#include "subject.h"

class Tile: public Observer, public Subject {
    const int resource;
    const int index;
    const int diceValue;

  public:
    Tile(int resource, int index, int diceValue)
        : resource(resource), index(index), diceValue(diceValue) {};

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    bool hasGeese();

    Info getInfo() const override;
};

#endif
