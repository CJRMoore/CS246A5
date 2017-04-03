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
    Info info{BuildingType::Path, owner, index, tripped?ResourceType::BRICK:ResourceType::PARK};
    return info;
}

vector<int> Path::upgradeRequirements(Builder &b){
    vector<int> theRequirements(5,0);
    theRequirements[3] = 1; // 1 Heat
    theRequirements[4] = 1; // 1 Wifi

    if (theRequirements.size()>0) owner = b.getColour();
    return theRequirements;
}


void Path::notify(Subject &whoNotified){
    cout << "PATH NOTIFIED";
    Info info = whoNotified.getInfo();
    if (info.owner!=BuilderType::None) {
        cout << " & NOTIFYING OBSERVERS";
        tripped = true;
        notifyObservers(SubscriptionType::Tile);
        tripped = false;
    }
    cout << endl;
}
