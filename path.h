#ifndef PATH_H
#define PATH_H
#include "abstractpath.h"

class Path: public AbstractPath{
  public:
    Path(int index): AbstractPath(index) {};
    ~Path() {};
    Info getInfo() const override;

    bool hasRoad() const override { return false; };
};

#endif
