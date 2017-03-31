#ifndef INFO_H
#define INFO_H
#include "resources.h"
#include "buildingtypes.h"
#include "buildertype.h"

struct Info {
    BuildingType buildingType;
    BuilderType owner;
    int index;
    ResourceType resource;
};
#endif
