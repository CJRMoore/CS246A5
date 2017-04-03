#include "address.h"
#include "subscriptions.h"
#include "buildingtypes.h"
#include "info.h"
#include "buildertype.h"
#include "builder.h"

using namespace std;

#include <iostream>
void Address::notify(Subject &whoNotified){
    Info info = whoNotified.getInfo();
    if (whoNotified.getInfo().owner == BuilderType::Check && owner!=BuilderType::None){
        notifyObservers(SubscriptionType::Path);
    }
    triggeredResource = whoNotified.getInfo().resource;
    if (owner == BuilderType::None) return;
    notifyObservers(SubscriptionType::Address);
    notifyObservers(SubscriptionType::Tile);
}

Info Address::getInfo() const {
    Info info{BuildingType::Address, owner, index, triggeredResource};
    return info;
}

vector<int> Address::upgradeRequirements(Builder &b){
    vector<int> theRequirements(5,0);

    owner = BuilderType::Check;
    adjacent = true;
    if (adjacent==true) {
        owner = BuilderType::None;
        throw(string("Cannot build residence adjacent to another."));
    }
    owner = BuilderType::None;

    theRequirements[0] = 1; // 1 brick
    theRequirements[1] = 1; // 1 energy
    theRequirements[2] = 1; // 1 glass
    theRequirements[4] = 1; // 1 wifi

    if (theRequirements.size()>0) {
        shared_ptr<Builder> pb;
        pb.reset(&b);
        attach(pb);
        owner = b.getColour();
    }
    return theRequirements;
}
