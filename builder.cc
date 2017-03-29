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
    //theDice.resize(2);//,nullptr);
    //theDice[0] = make_unique<LoadedDice>();
    //theDice[1] = make_unique<FairDice>();
}

BuilderType Builder::getColour() {
    return colour;
}

void Builder::buildResidence(Address *a) {}

void Builder::buildRoad(Path *p) {}

void Builder::upgradeResidence(Residence *r) {}

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
