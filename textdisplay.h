#ifndef TEXIDISPLAY_H 
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>
#include <string>
#include "observer.h"
#include "subscriptions.h"

class Tile;

class TextDisplay: public Observer {
    std::vector<std::vector<std::string> > theDisplay;
    //const int gridSize; // Maybe make it expandable

  public:
    TextDisplay();

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    ~TextDisplay();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
