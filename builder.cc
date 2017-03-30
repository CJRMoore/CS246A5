#include "builder.h"
#include "path.h"
#include "address.h"
#include "loadeddice.h"
#include "fairdice.h"
#include "subscriptions.h"

using namespace std;

Builder::Builder(BuilderType colour): colour(colour){//, resources(vector<int>(5,0)){
    resources.resize(5,0);

    theDice.push_back(make_unique<LoadedDice>());
    theDice.push_back(make_unique<FairDice>());
    currDice = theDice[0];
}

BuilderType Builder::getColour() {
    return colour;
}

bool Builder::upgradeAddress(shared_ptr<AbstractAddress> a) {
    vector<int> req = a->upgradeRequirements();
    if (req.size()==0) return false;

    try{
        for (unsigned int i=0; i<resources.size(); i++) { 
            if (resources[i] < req[i])  throw(1);
        }
        return true;
    }
    catch(int){
        cout << "You do not have enough resources." << endl;
        return false;
    }
}

bool Builder::upgradePath(shared_ptr<Path> p) {
    vector<int> req = p->upgradeRequirements();
    if (req.size()==0) return false;

    try{
        for (unsigned int i=0; i<resources.size(); i++) { 
            if (resources[i] < req[i])  throw(1);
        }
        return true;
    }
    catch(int){
        cout << "You do not have enough resources." << endl;
        return false;
    }
}

bool Builder::isWon() {
    return false;
}

int Builder::roll(bool whichDice){
    if (whichDice>=theDice.size()) throw("INVALID_DICE");
    return theDice[whichDice]->rollDice();
}

void Builder::notify(Subject &whoNotified) {}

SubscriptionType Builder::subType() const {
    return SubscriptionType::All;
}
