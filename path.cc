#include "path.h"
#include "info.h"
#include "buildingtypes.h"
#include "resources.h"
#include <vector>

using namespace std;

Info Path::getInfo() const {
    Info info{BuildingType::Path, index, int(ResourceType::PARK)};
    return info;
}

vector<int> Path::upgradeRequirements(){
    vector<int> theRequirements(5,0);
    theRequirements[3] = 1; // 1 Heat
    theRequirements[4] = 1; // 1 Wifi
    return theRequirements;
}
