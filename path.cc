#include "path.h"
#include "info.h"
#include "buildingtypes.h"
#include "buildertype.h"
#include "resources.h"
#include "builder.h"
#include "subject.h"
#include <vector>

using namespace std;

Info Path::getInfo() const {
    Info info{BuildingType::Path, owner, index, resource};
    return info;
}

vector<int> Path::upgradeRequirements(Builder &b){
    vector<int> theRequirements(5,0);
    theRequirements[3] = 1; // 1 Heat
    theRequirements[4] = 1; // 1 Wifi

    // These change when notifyObserver is called
    validPlacement = false;
    underConsideration = true;
    owner = b.getColour();
    resource = ResourceType::BRICK;

    notifyObservers(SubscriptionType::Path);
    notifyObservers(SubscriptionType::Tile);

    if (!validPlacement) {
        validPlacement = false;
        underConsideration = false;
        throw(string("Invalid location for road; must be adjacent to a building or another road."));
    }
    owner = BuilderType::None;
    resource = ResourceType::PARK;
    validPlacement = false;
    underConsideration = false;

    if (theRequirements.size()>0) owner = b.getColour();
    return theRequirements;
}


void Path::notify(Subject &whoNotified){
    Info info = whoNotified.getInfo();

    if (info.buildingType==BuildingType::Path && owner==info.owner && owner!=BuilderType::None && index!=info.index){
        if (underConsideration){
            validPlacement = true;
        }
        else if (info.resource!=ResourceType::PARK){
            notifyObservers(SubscriptionType::Path);
        }
        return;
    }
    else if (info.buildingType==BuildingType::Address && info.owner==owner && owner!=BuilderType::None){
        if (underConsideration) validPlacement = true;
        return;
    }
}
