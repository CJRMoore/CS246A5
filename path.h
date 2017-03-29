#ifndef PATH_H
#define PATH_H
#include "abstractpath.h"

class Path: public AbstractPath{
  public:
    Info getInfo() const override;

    bool hasRoad() const override;
};

#endif
