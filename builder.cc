#include "builder.h"
#include "path.h"
#include "address.h"
#include "loadeddice.h"
#include "fairdice.h"
#include "subscriptions.h"
#include "basement.h"
#include "house.h"
#include "tower.h"
#include "road.h"
#include "path.h"

#include <sstream>

using namespace std;

vector<string> Builder::playerColours = vector<string>(0);

Builder::Builder(BuilderType colour): colour(colour), rolled(false), numPoints(0){
    resources.resize(5,99);

    theDice.push_back(make_unique<LoadedDice>());
    theDice.push_back(make_unique<FairDice>());
    currDice = theDice[0];
}

BuilderType Builder::getColour() {
    return colour;
}

void Builder::setDice(bool whichDice){
    currDice = theDice[whichDice];
}

shared_ptr<AbstractAddress> Builder::buildAtAddress(shared_ptr<AbstractAddress> a) {
    vector<int> req = a->upgradeRequirements(*this);
    if (req.size()==0) {
        cout << "Invalid location." << endl;
        return a;
    }

    try{
        for (unsigned int i=0; i<resources.size(); i++) {
            if (resources[i] < req[i])  throw(1);
        }
        shared_ptr<AbstractAddress> na;
        if (req[0]!=1) {
            stringstream ss;
            ss << "Property exists at " << a->getIndex() << ".";
            throw(ss.str());
        }
        else na = make_shared<Basement>(a);
        numPoints++;
        return na;
    }
    catch(int){
        cout << "You do not have enough resources." << endl;
        return a;
    }
}

shared_ptr<AbstractAddress> Builder::upgradeAddress(shared_ptr<AbstractAddress> a) {
    vector<int> req = a->upgradeRequirements(*this);
    if (req.size()==0) {
        cout << "Invalid location." << endl;
        return a;
    }

    try{
        for (unsigned int i=0; i<resources.size(); i++) { 
            if (resources[i] < req[i])  throw(1);
        }
        shared_ptr<AbstractAddress> na;
        if (req[0]==1) {
            stringstream ss;
            ss << "No property exists at " << a->getIndex() << ".";
            throw(ss.str());
        }
        if (req[0]==0) na = make_shared<House>(a);
        else na = make_shared<Tower>(a);
        numPoints++;
        return na;
    }
    catch(int){
        cout << "You do not have enough resources." << endl;
        return a;
    }
}


shared_ptr<AbstractPath> Builder::upgradePath(shared_ptr<AbstractPath> p) {
    vector<int> req = p->upgradeRequirements(*this);
    if (req.size()==0) {
        cout << "Road already built at " << p->getIndex() << "." << endl;
        return p;
    }

    try{
        for (unsigned int i=0; i<resources.size(); i++) { 
            if (resources[i] < req[i])  throw(1);
        }
        shared_ptr<AbstractPath> np = make_shared<Road>(p);
        return np;
    }
    catch(int){
        cout << "You do not have enough resources." << endl;
        return p;
    }
}


bool Builder::isWon() {
    return false;
}

int Builder::roll(){
    if (rolled) throw(string("Already rolled."));
    int r = currDice->rollDice();
    rolled = true;
    return r;
}

void Builder::notify(Subject &whoNotified) {
    Info info = whoNotified.getInfo();
    if (info.resource != ResourceType::PARK){
        resources[int(info.resource)]++;
    }
}

SubscriptionType Builder::subType() const {
    return SubscriptionType::Address;
}

void Builder::resetResources(){
    for (int i=0; i<resources.size(); i++) resources[i] = 0;
}


ostream &operator<<(ostream &out, shared_ptr<Builder> b){
    out << b->playerColours[int(b->colour)] << " has " << b->numPoints << " points, " << b->resources[0] << " brick, " << b->resources[1] << " energy, " << b->resources[2] << " glass, " << b->resources[3] << " heat, and " << b->resources[4] << " WiFi." << endl;
    return out;
}
