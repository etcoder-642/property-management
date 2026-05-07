#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "../include/registry.h"

using namespace std;

int OwnerRegistry::addOwner(Owner &owner)
{
    owner.setOwnerID(nextID++);
    owners.push_back(owner);
    return owner.getOwnerID();
}

int TenantRegistry::addTenant(Tenant &tenant)
{
    tenant.setTenantID(nextID++);
    tenants.push_back(tenant);
    return tenant.getTenantID();
}

int PropertyRegistry::addProperty(Property &property)
{
    property.setPropertyID(nextID++);
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
    vector<double> tempDimensions = prop->getDimensions();
    string tempDimensionStr;
    for (double d : tempDimensions)
    {
        ostringstream oss;
        oss << fixed << setprecision(1) << d;
        tempDimensionStr += oss.str() + " ";
    }
    double tempRentalValue = prop->getRentalValue();
    return {tempLocation, tempType, tempDesc, to_string(tempRentalValue), tempDimensionStr, to_string(id)};
}

vector<vector<string>> PropertyRegistry::getPropertyFromOwner(Owner &owner)
{
    vector<vector<string>> res;
    vector<int> properties = owner.getPropertyIDs();
    for (int i : properties)
    {
        vector<string> temp = getFormattedPropertyData(i);
        if(temp.empty()) continue;
        res.push_back(temp);
    }
    return res;
}