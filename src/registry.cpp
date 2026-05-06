#include <iostream>
#include <string>
#include <vector>
#include "../include/registry.h"

using namespace std;

void OwnerRegistry::addOwner(Owner& owner){
    nextID++;
    owner.setOwnerID(nextID);
    owners.push_back(owner);
}


