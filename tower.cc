#include "tower.h"
#include "subscriptions.h"
#include "buildingtypes.h"
#include "info.h"
#include "builder.h"
#include <memory>

using namespace std;

Tower::Tower(shared_ptr<AbstractAddress> aa)
    : Residence(aa) 
{
    shared_ptr<Tower> tmp;
    tmp.reset(this);
    aa->attach(tmp);
}

Info Tower::getInfo() const {
    Info info{BuildingType::Address, owner, index, triggeredResource};
    return info;
}

void Tower::notify(Subject &whoNotified){
    triggeredResource = whoNotified.getInfo().resource;
    notifyObservers(SubscriptionType::Builder);
    notifyObservers(SubscriptionType::Tile);
}


vector<int> Tower::upgradeRequirements(Builder &b){
    if (owner!=b.getColour()) {
        cout << "Address already owned." << endl;
    }
    return vector<int>(0);
}
