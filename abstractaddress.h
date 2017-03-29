#ifndef ABSTRACTADDRESS_H
#define ABSTRACTADDRESS_H
#include "subject.h"
#include "observer.h"
#include "buildingtype.h"

class Info;

class AbstractAddress: public Observer, public Subject {
    const int index;
    BuildingType building;

  public:
    AbstractAddress(int index): index(index), building(BuildingType::None) {};
};

#endif
