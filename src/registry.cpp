#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "../include/registry.h"

using namespace std;

int OwnerRegistry::addOwner(Owner &owner)
{
    owner.setOwnerID(++nextID);
    owners.push_back(owner);
    return owner.getOwnerID();
}

int TenantRegistry::addTenant(Tenant &tenant)
{
    tenant.setTenantID(++nextID);
    tenants.push_back(tenant);
    return tenant.getTenantID();
}

int PropertyRegistry::addProperty(Property &property)
{
    property.setPropertyID(++nextID);
    properties.push_back(property);
    return property.getPropertyID();
}

Property *PropertyRegistry::getPropertyByID(int propertyID)
{
    for (Property &p : properties)
    {
        if (propertyID == p.getPropertyID())
        {
            return &p;
        }
    }
    return nullptr;
}

bool PropertyRegistry::removePropertyByID(int id)
{
    for(int i = 0; i < properties.size(); i++)
    {
        if(properties[i].getPropertyID() == id)
        {
            properties.erase(properties.begin() + i);
            return true;
        }
    }
    return false;
}

bool PropertyRegistry::listProperty(int id)
{
    for(int i = 0; i < properties.size(); i++)
    {
        if(properties[i].getPropertyID() == id)
        {
            properties[i].setIsListed(true);
            return true;
        }
    }
    return false;
}


bool PropertyRegistry::delistProperty(int id)
{
    for(int i = 0; i < properties.size(); i++)
    {
        if(properties[i].getPropertyID() == id)
        {
            properties[i].setIsListed(false);
            return true;
        }
    }
    return false;
}

vector<string> PropertyRegistry::getFormattedPropertyData(int id)
{
    Property *prop = getPropertyByID(id);
    if (prop == nullptr)
    {
        cout << "here's the problem" << endl;
        return {};
    }
    string tempLocation = prop->getLocation();
    string tempType = prop->getType();
    string tempDesc = prop->getDescription();
    double tempArea = prop->getArea();
    double tempRentalValue = prop->getRentalValue();
    return {tempLocation, tempType, tempDesc, to_string(tempRentalValue), to_string(tempArea), to_string(id)};
}
