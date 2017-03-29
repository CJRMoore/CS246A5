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
    Info info{0,0};
    return info;
}
