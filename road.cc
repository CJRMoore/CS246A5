#include "road.h"

Road::Road(AbstractPath *ap): ap(ap) {}

int Road::getIndex(){
    return ap->getIndex();
}
