#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include "property.h"

using namespace std;

class OwnerRegistry {
private:
    vector<Owner> owners;
    int nextID = -1;
public:
    OwnerRegistry() {}

    void addOwner(Owner& owner);
};

class tenantRegistry {
private:
   vector<Tenant> tenants;
   int nextID = -1;
public:
   tenantRegistry() {}

   void addTenant(Tenant& tenant);
};

class propertyRegistry {
private:
    vector<Property> properties;
    int nextID = -1;
public:
    propertyRegistry() {}

    void addProperty(Property& property);
};

class contractRegistry {
private:
    vector<Contract> contracts;
    int nextID = -1;
public:
    contractRegistry() {}

    void addContract(Contract& contract);
};

#endif // REGISTRY_H