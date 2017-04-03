#ifndef ROAD_H
#define ROAD_H
#include "abstractpath.h"
#include "subject.h"
#include <vector>
#include <memory>

class Info;
class Builder;

class Road: public AbstractPath {
    std::shared_ptr<AbstractPath> ap;

  public:
    Road(std::shared_ptr<AbstractPath> ap);
    ~Road() {};

    bool hasRoad() const override { return true; };
    int getIndex() override;    
    Info getInfo() const override;

    void notify(Subject &whoNotified) override;

    std::vector<int> upgradeRequirements(Builder &b) override;
    void setOwner(BuilderType o) override { ap->setOwner(o); }


};

#endif
