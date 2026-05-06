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

void TenantRegistry::addTenant(Tenant& tenant){
    nextID++;
    tenant.setTenantID(nextID);
    tenants.push_back(tenant);
}

