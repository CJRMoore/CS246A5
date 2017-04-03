#include "house.h"
#include "subscriptions.h"
#include "buildingtypes.h"
#include "info.h"
#include "builder.h"
#include <memory>

using namespace std;

House::House(shared_ptr<AbstractAddress> aa)
    : Residence(aa) 
{
    shared_ptr<House> tmp;
    tmp.reset(this);
    aa->attach(tmp);
}

Info House::getInfo() const {
    Info info{BuildingType::Address, owner, index, triggeredResource};
    return info;
}

void House::notify(Subject &whoNotified){
    triggeredResource = whoNotified.getInfo().resource;
    notifyObservers(SubscriptionType::Address);
    notifyObservers(SubscriptionType::Tile);
}

vector<int> House::upgradeRequirements(Builder &b){
    vector<int> theRequirements(5,0);
    if (owner!=b.getColour()) {
        cout << int(owner) << " " << int(b.getColour()) << endl;
        cout << "Address " << getIndex() << " already owned." << endl;
        return theRequirements;
    }

    theRequirements[0] = 3; // 3 brick
    theRequirements[1] = 2; // 2 energy
    theRequirements[2] = 2; // 2 glass
    theRequirements[3] = 2; // 2 heat
    theRequirements[4] = 1; // 1 wifi

    if (theRequirements.size()>0) {
        shared_ptr<Builder> pb;
        pb.reset(&b);
        attach(pb);
    }
    return theRequirements;
}

