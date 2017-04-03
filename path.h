#ifndef PATH_H
#define PATH_H
#include "abstractpath.h"
#include <vector>

class Builder;

class Path: public AbstractPath{
    BuilderType owner;

  public:
    Path(int index): AbstractPath(index) {};
    ~Path() {};
    
    // Subject Overrides
    Info getInfo() const override;

    // Observer overrides
    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    bool hasRoad() const override { return false; };
    
    std::vector<int> upgradeRequirements(Builder &b) override;
};

#endif
