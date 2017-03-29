#include "residence.h"
#include "subscriptions.h"
#include "info.h"
#include <memory>

using namespace std;

Residence::Residence(AbstractAddress *aa, int index)
    : AbstractAddress(index), aa(aa){}

void Residence::upgrade(){
    if (upgradeProgress>=2) throw("MAX_UPGRADE");

    upgradeProgress++;
    notifyObservers(SubscriptionType::All);
}

Info Residence::getInfo() const {
    Info info{-1,-1};
    return info;
}

void Residence::notify(Subject &whoNotified){
    Info info = whoNotified.getInfo();
    notifyObservers(SubscriptionType::Builder);
}

SubscriptionType Residence::subType() const {
    return SubscriptionType::Tile;
}
