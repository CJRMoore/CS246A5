#ifndef GEESE_H
#define GEESE_H
#include "resources.h"
#include "subscriptions.h"
#include "observer.h"
#include "subject.h"
#include "tile.h"
#include <memory>

class Geese: public Tile {
    std::shared_ptr<Tile> currTile;

  public:
    Geese(std::shared_ptr<Tile> currTile)
        : currTile(currTile) {};

    int getDiceValue() override { return currTile->getDiceValue(); };
    int getIndex() override { return currTile->getIndex(); };

    Info getInfo() const override;
};

#endif
