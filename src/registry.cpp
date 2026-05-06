#include <iostream>
#include <string>
#include <vector>
#include "../include/registry.h"

using namespace std;

int OwnerRegistry::addOwner(Owner& owner){
    owner.setOwnerID(nextID++);
    owners.push_back(owner);
    return owner.getOwnerID();
}

int TenantRegistry::addTenant(Tenant& tenant){
    tenant.setTenantID(nextID++);
    tenants.push_back(tenant);
    return tenant.getTenantID();
}

int PropertyRegistry::addProperty(Property& property){
    property.setPropertyID(nextID++);
    properties.push_back(property);
    return property.getPropertyID();
}

Property* PropertyRegistry::getPropertyByID(int propertyID)
{
    for(Property &p: properties)
    {
        if(propertyID == p.getPropertyID()){
            return &p;
        }
    }
    return nullptr;
}