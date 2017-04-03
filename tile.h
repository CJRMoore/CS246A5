#ifndef TILE_H
#define TILE_H
#include "resources.h"
#include "subscriptions.h"
#include "observer.h"
#include "subject.h"

class Tile: public Observer, public Subject {
  protected:
    const ResourceType resource;
    const int index;
    const int diceValue;

  public:
    Tile(int resource, int index, int diceValue)
        : resource(ResourceType(resource)), index(index), diceValue(diceValue) {};
    Tile() : resource(ResourceType::PARK), index(-1), diceValue(-1) {};

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;
    virtual int getDiceValue(){ return diceValue; };
    virtual int getIndex(){ return index; };

    bool hasGeese();

    Info getInfo() const override;
};

#endif
