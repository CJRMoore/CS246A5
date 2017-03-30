#include "road.h"
#include "subject.h"
#include "buildingtypes.h"
#include "info.h"
#include <vector>

using namespace std;

Road::Road(shared_ptr<AbstractPath> ap): AbstractPath(ap->getIndex()), ap(ap) {}

int Road::getIndex(){
    return ap->getIndex();
}

Info Road::getInfo() const {
    Info info{BuildingType::Path,index,int(ResourceType::PARK)};
    return info;
}

vector<int> Road::upgradeRequirements() {
    return vector<int>(0);
}
