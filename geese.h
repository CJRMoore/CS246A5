#ifndef GEESE_H
#define GEESE_H

class Tile;

class Geese {
    Tile *currTile;
  public:
    void moveTo(Tile *t);
};

#endif
