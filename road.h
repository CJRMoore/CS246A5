#ifndef ROAD_H
#define ROAD_H
#include "abstractpath.h"

class Road: public AbstractPath {
    AbstractPath *ap;

  public:
    Road(AbstractPath *ap);

    bool hasRoad() const override { return true; };
    int getIndex() override;    
};

#endif
