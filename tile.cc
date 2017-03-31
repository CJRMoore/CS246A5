#include "tile.h"
#include "info.h"
#include "buildingtypes.h"
#include "buildertype.h"

#include <iostream>
using namespace std;

void Tile::notify(Subject &whoNotified){
    notifyObservers(SubscriptionType::Tile);
}


SubscriptionType Tile::subType() const { 
    return SubscriptionType::All; 
}

bool Tile::hasGeese() {
    return false;
}

Info Tile::getInfo() const {
    Info info{BuildingType::Tile, BuilderType::None, index, resource};
    return info;
}
