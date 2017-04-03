#include "road.h"
#include "subject.h"
#include "buildingtypes.h"
#include "info.h"
#include "buildertype.h"
#include <vector>

using namespace std;

Road::Road(shared_ptr<AbstractPath> ap): AbstractPath(ap->getIndex()), ap(ap) {}

int Road::getIndex(){
    return ap->getIndex();
}

Info Road::getInfo() const {
    Info info{BuildingType::Path,owner,index,ResourceType::PARK};
    return info;
}

vector<int> Road::upgradeRequirements(Builder &b) {
    return vector<int>(0);
}

void Road::notify(Subject &whoNotified){
    Info info = whoNotified.getInfo();
    if (info.owner!=BuilderType::None) notifyObservers(SubscriptionType::Tile);
}
