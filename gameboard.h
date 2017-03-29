#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <string>
#include <memory>
#include "tile.h"
#include "abstractpath.h"
#include "abstractaddress.h"
#include "geese.h"

class GameBoard {
    std::vector<std::shared_ptr<Tile> > theBoard; // the geese may point to a tile object
    std::vector<std::shared_ptr<AbstractAddress> > theAddresses;
    std::vector<std::shared_ptr<AbstractPath> > thePaths;

    Geese g;

  public:
    void Init(std::string boardFile);
    //void Init(int n);
    void moveGeese(int t);
    void save(std::string sFile);
    void load(std::string lFile);
};

#endif
