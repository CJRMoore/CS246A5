#include "tile.h"
#include "info.h"

void Tile::notify(Subject &whoNotified){

}


SubscriptionType Tile::subType() const { 
    return SubscriptionType::Tile; 
}

bool Tile::hasGeese() {
    return false;
}

Info Tile::getInfo() const {
    Info info{index, resource};
    return info;
}
