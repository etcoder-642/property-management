#include <iostream>
#include <string>
#include <vector>
#include "../include/registry.h"

using namespace std;

void OwnerRegistry::addOwner(const Owner& owner){
    owners.push_back(owner);
}


