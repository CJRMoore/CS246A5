#ifndef RESIDENCE_H
#define RESIDENCE_H
#include "subject.h"
#include "abstractaddress.h"
#include <memory>

class Info;

class Residence: public AbstractAddress {
    AbstractAddress *aa;
    int upgradeProgress;

  public:
    Residence(AbstractAddress *aa, int index);
    void upgrade();

    Info getInfo() const override;
};

#endif
