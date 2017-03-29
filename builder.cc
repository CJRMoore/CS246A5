#include "builder.h"
#include "path.h"
#include "address.h"
#include "loadeddice.h"
#include "fairdice.h"

using namespace std;

Builder::Builder(BuilderType colour): colour(colour){//, resources(vector<int>(5,0)){
    resources.resize(5,0);

    theDice.resize(2);//,nullptr);
    theDice[0] = make_unique<LoadedDice>();
    theDice[1] = make_unique<FairDice>();
}
