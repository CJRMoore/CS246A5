#include "road.h"

Road::Road(AbstractPath *ap): ap(ap) {}

Road::~Road(){
    delete ap;
}


