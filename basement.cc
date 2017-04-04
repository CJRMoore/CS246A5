#include "basement.h"
#include "subscriptions.h"
#include "buildingtypes.h"
#include "info.h"
#include "residence.h"
#include "builder.h"
#include <memory>

using namespace std;
#include <iostream>
Basement::Basement(shared_ptr<AbstractAddress> aa)
    : Residence(aa) 
{
    shared_ptr<Basement> tmp{this};
    aa->attach(tmp);
}

Info Basement::getInfo() const {
    Info info{BuildingType::Address, owner, index, triggeredResource};
    return info;
}

void Basement::notify(Subject &whoNotified){
    Info info = whoNotified.getInfo();

    if (info.buildingType==BuildingType::Path) {
        notifyObservers(SubscriptionType::Path);
    }
    else if (info.buildingType==BuildingType::Tile){
        triggeredResource = whoNotified.getInfo().resource;
        notifyObservers(SubscriptionType::Address);
        notifyObservers(SubscriptionType::Tile);
    }
}


vector<int> Basement::upgradeRequirements(Builder &b){
    vector<int> theRequirements(5,0);
    if (owner!=b.getColour()) {
        cout << "Address " << getIndex() << " already owned." << endl;
        return theRequirements;
    }
    theRequirements[2] = 2; // 2 glass
    theRequirements[3] = 3; // 3 heat

    if (theRequirements.size()>0) {//attach(make_shared<Builder>(b));
        shared_ptr<Builder> pb{&b};
        attach(pb);
    }
    return theRequirements;
}

