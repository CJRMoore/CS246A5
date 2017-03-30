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

    std::vector<std::unique_ptr<Builder> > thePlayers;
    std::vector<std::string> theColours;

    Geese g;

  public:
    void Init(std::string boardFile);
    void moveGeese(int t);
    void save(std::string sFile);
    void load(std::string lFile);
};

#endif
