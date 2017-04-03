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
#include <algorithm>

using namespace std;

vector<string> Builder::playerColours = vector<string>(0);
vector<string> Builder::resourceStr = vector<string>(0);

Builder::Builder(BuilderType colour)
: colour(colour), numPoints(0)
{
    resources.resize(5,99);
    turnGains.resize(5,0);

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
        for (int i=0; i<resources.size(); i++) resources[i] -= req[i];
        ownedAddresses.push_back(a);
        numPoints++;
        return na;
    }
    catch(int){
        cout << "You do not have enough resources." << endl;
        return a;
    }
    catch(string s){
        cout << s << endl;
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
        for (int i=0; i<resources.size(); i++) resources[i] -= req[i];
        numPoints++;
        for (int j=0; j<ownedAddresses.size(); j++){
            if (ownedAddresses[j]->getIndex() == a->getIndex()){
                ownedAddresses[j] = a;
                break;
            }
        }
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
        for (int i=0; i<resources.size(); i++) resources[i] -= req[i];
        ownedRoads.push_back(p);
        return np;
    }
    catch(int){
        cout << "You do not have enough resources." << endl;
        return p;
    }
}

void Builder::restorePlayerStats(GameBoard &g, std::string &s){
    stringstream ss(s);
    vector<int> res(5);
    ss >> resources[0] >> resources[1] >> resources[2] >> resources[3] >> resources[4];
    vector<int> tmpRes = resources;
    resources = std::vector<int>(5,9999); // building and upgrading checks player resource values
                                          // ensures buildings and roads will be completed
    string l;
    ss >> l;
    shared_ptr<Builder> me;
    me.reset(this);
    // Player owned roads
    if (l == "r"){
        string l2;
        while (ss >> l2){
            if (l2=="h"){
                l = l2;
                break;
            }
            stringstream ss2(l2);
            int r; 
            ss2 >> r;
            g.buildRoad(me, r);
        }
    }
    // Player owned residences (should be at least one)
    if (l == "h"){
        int a; 
        string residence; 
        while (ss >> a >> residence){ // rest of line only has this data
            if (ss.fail()) break;
            g.buildResidence(me,a);
            if (residence=="H" || residence=="T") g.upgradeResidence(me,a);
            if (residence=="T") g.upgradeResidence(me,a);
        }
    }
    resources = tmpRes;
}


string Builder::listOwnedResidences(){
    stringstream ss;
    //for (int i=0; i<ownedPaths.size(); i++){
    //    ss << "\t" << ownedPaths[i]->getIndex() << " Path" << endl;
    //}
    for (int i=0; i<ownedAddresses.size(); i++){
        int rl = ownedAddresses[i]->getResLevel();
        int ind = ownedAddresses[i]->getIndex();
        ss << "\t" << (ind<10?" ":"") << ind << " " << (rl>0?(rl>1?"T":"H"):"B") << endl;
    }

    return ss.str();
}





bool Builder::isWon() {
    return numPoints>=10?true:false;
}

int Builder::roll(){
    //if (rolled) throw(string("Already rolled."));
    int r = currDice->rollDice();
    //rolled = true;
    return r;
}

void Builder::notify(Subject &whoNotified) {
    Info info = whoNotified.getInfo();
    if (info.resource != ResourceType::PARK){
        resources[int(info.resource)]++;
        turnGains[int(info.resource)]++;
    }
}

void Builder::printTurnGains(){
    if (!(std::any_of(turnGains.begin(), turnGains.end(), [](int i){ return i>0; } ))) return;
    cout << "Builder " << playerColours[int(colour)] << " gained:" << endl;
    for (int i=0; i<resources.size(); i++){
        if (turnGains[i]>0) cout << "\t" << turnGains[i] << " " << resourceStr[i] << endl;
        turnGains[i] = 0;
    }
}

string Builder::getNumPoints(){
    stringstream ss;
    ss << numPoints;
    return ss.str();
}

SubscriptionType Builder::subType() const {
    return SubscriptionType::Address;
}

void Builder::resetResources(){
    for (int i=0; i<resources.size(); i++) resources[i] = 0;
}


ostream &operator<<(ostream &out, const shared_ptr<Builder> b){
    out << b->playerColours[int(b->colour)] << " has " << b->numPoints << " points, " << b->resources[0] << " brick, " << b->resources[1] << " energy, " << b->resources[2] << " glass, " << b->resources[3] << " heat, and " << b->resources[4] << " WiFi." << endl;
    return out;
}

ofstream &operator<<(ofstream &out, const shared_ptr<Builder> b){
    for (int i=0; i<b->resources.size(); i++) out << b->resources[i]  << " ";
    if (b->ownedRoads.size()>0) out << "r ";
    for (int i=0; i<b->ownedRoads.size(); i++) out << b->ownedRoads[i]->getIndex() << " ";
    if (b->ownedAddresses.size()>0) out << "h ";
    for (int i=0; i<b->ownedAddresses.size(); i++){
        int bt = b->ownedAddresses[i]->getResLevel();
        out << b->ownedAddresses[i]->getIndex() << " " << (bt>0?(bt==1?"H":"T"):"B");
    }
    out << endl;

    return out;
}
