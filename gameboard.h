#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <string>
#include <memory>
#include "tile.h"
#include "abstractpath.h"
#include "abstractaddress.h"
#include "geese.h"

class Builder;

class GameBoard {
    std::vector<std::shared_ptr<Tile> > theBoard; // the geese may point to a tile object
    std::vector<std::shared_ptr<AbstractAddress> > theAddresses;
    std::vector<std::shared_ptr<AbstractPath> > thePaths;

    //std::vector<std::unique_ptr<Builder> > thePlayers;
    std::vector<std::string> theColours;

    Geese g;

  public:
    void Init(std::string boardFile, std::vector<std::shared_ptr<Builder> > &thePlayers);
    void moveGeese(int t);
    std::string save();
    void load(std::string lFile);

    void buildRoad(std::shared_ptr<Builder> &b, int index);
    void buildResidence(std::shared_ptr<Builder> &b, int index);
    void upgradeResidence(std::shared_ptr<Builder> &b, int index);

    void distributeResources(int roll);

    std::vector<std::string> getColours() { return theColours; };
};

#endif
