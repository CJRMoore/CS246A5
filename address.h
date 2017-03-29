#ifndef ADDRESS_H
#define ADDRESS_H
#include "abstractaddress.h"

class Address: public AbstractAddress {
  public:
    Address(int index): AbstractAddress(index) {};
};

#endif
