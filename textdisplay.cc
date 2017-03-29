#include "textdisplay.h"
#include "tile.h"
#include "info.h"
#include "subscriptions.h"
#include <iostream>
#include <utility>

using namespace std;

TextDisplay::TextDisplay() { 
    theDisplay.resize(41);
}

TextDisplay::~TextDisplay() {}

void TextDisplay::notify(Subject &whoNotified){
//    Info info = whoNotified.getInfo();
}


SubscriptionType TextDisplay::subType() const {
    return SubscriptionType::All;
}

// Overload operator for text output
ostream &operator<<(ostream &out, const TextDisplay &td) {
    out << "Call to TextDisplay" << endl;
    return out;
}

