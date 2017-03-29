#include "resources.h"
#include <iostream>

istream &operator>>(istream &in, ResourceType &r){
    in >> r.resource;
    return in;    
}
