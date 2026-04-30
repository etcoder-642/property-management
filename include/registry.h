#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include "property.h"

using namespace std;

class OwnerRegistry {
private:
    vector<Owner> owners;
public:
    OwnerRegistry() {}

    void addOwner(const Owner& owner);
};

#endif // REGISTRY_H