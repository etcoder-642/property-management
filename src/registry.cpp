#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <direct.h>

#include "../include/registry.h"

using namespace std;

int OwnerRegistry::addOwner(Owner &owner)
{
    owner.setOwnerID(++nextID);
    owners.push_back(owner);
    return owner.getOwnerID();
}

Owner *OwnerRegistry::verifyData(vector<string> input)
{
    for (int i = 0; i < owners.size(); i++)
    {
        if (owners[i].getName() == input[0] && owners[i].getPassword() == input[1])
        {
            return &owners[i];
        }
    }
    return nullptr;
}
void OwnerRegistry::saveToFile()
{
    _mkdir("data");
    ofstream file("data/owner.txt");

    for (Owner o : owners)
    {
        file << o.getOwnerID() << ","
             << o.getName() << ","
             << o.getPassword() << ",";

        vector<int> ids = o.getPropertyIDs();
        for (int i = 0; i < ids.size(); i++)
        {
            if (i > 0)
                file << ";";
            file << ids[i];
        }
        file << endl;
    }

    file.close();
}
void OwnerRegistry::loadFromFile()
{
    ifstream file("data/owner.txt");

    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> data;
        string value;

        while (getline(ss, value, ','))
            data.push_back(value);

        if (data.size() < 3)
            continue;

        Owner o(data[1], data[2]); // name, password
        o.setOwnerID(stoi(data[0]));

        // parse the "5;7;9" part into individual property IDs
        if (data.size() >= 4 && !data[3].empty())
        {
            stringstream idStream(data[3]);
            string idStr;
            while (getline(idStream, idStr, ';'))
            {
                if (!idStr.empty())
                    o.addProperty(stoi(idStr));
            }
        }

        owners.push_back(o);

        if (o.getOwnerID() > nextID)
            nextID = o.getOwnerID();
    }

    file.close();
}
int TenantRegistry::addTenant(Tenant &tenant)
{
    tenant.setTenantID(++nextID);
    tenants.push_back(tenant);
    return tenant.getTenantID();
}

Tenant *TenantRegistry::verifyData(vector<string> input)
{
    for (int i = 0; i < tenants.size(); i++)
    {
        if (tenants[i].getName() == input[0] && tenants[i].getPassword() == input[1])
        {
            return &tenants[i];
        }
    }
    return nullptr;
}
void TenantRegistry::saveToFile()
{
    _mkdir("data");
    ofstream file("data/tenant.txt");
    for (Tenant t : tenants)
    {
        file << t.getTenantID() << ","
             << t.getName() << ","
             << t.getPassword()
             << endl;
    }
    file.close();
}

void TenantRegistry::loadFromFile()
{
    ifstream file("data/tenant.txt");
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> data;
        string value;
        while (getline(ss, value, ','))
            data.push_back(value);

        if (data.size() < 3)
            continue;

        Tenant t(data[1], data[2]);
        t.setTenantID(stoi(data[0]));
        tenants.push_back(t);

        if (t.getTenantID() > nextID)
            nextID = t.getTenantID();
    }
    file.close();
}
int PropertyRegistry::addProperty(Property &property)
{
    property.setPropertyID(++nextID);
    properties.push_back(property);
    return property.getPropertyID();
}

int ContractRegistry::addContract(Contract &contract)
{
    contract.setContractID(++nextID);
    contracts.push_back(contract);
    return contract.getContractID();
}

Contract *ContractRegistry::getContractByID(int contractID)
{
    for (Contract &t : contracts)
    {
        if (contractID == t.getContractID())
        {
            return &t;
        }
    }
    return nullptr;
}

bool ContractRegistry::activateContractByID(int contractID)
{
    for (int i = 0; i < contracts.size(); i++)
    {
        if (contracts[i].getContractID() == contractID)
        {
            contracts[i].setIsActive(true);
            return true;
        }
    }
    return false;
}
void ContractRegistry::saveToFile()
{
    _mkdir("data");
    ofstream file("data/contract.txt");
    for (Contract c : contracts)
    {
        Date d = c.getDate();
        file << c.getContractID() << ","
             << c.getOwnerID() << ","
             << c.getTenantID() << ","
             << c.getPropertyID() << ","
             << c.getIsActive() << ","
             << d.day << ","
             << d.month << ","
             << d.year << ","
             << c.getRentalAmount() << ","
             << c.getContractDuration()
             << endl;
    }
    file.close();
}

void ContractRegistry::loadFromFile()
{
    ifstream file("data/contract.txt");
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> data;
        string value;
        while (getline(ss, value, ','))
            data.push_back(value);

        if (data.size() < 10)
            continue;

        Date d;
        d.day = stoi(data[5]);
        d.month = stoi(data[6]);
        d.year = stoi(data[7]);

        Contract c(stoi(data[1]), stoi(data[2]), stoi(data[3]), d, stod(data[8]), stoi(data[9]));
        c.setContractID(stoi(data[0]));
        c.setIsActive(stoi(data[4]));
        contracts.push_back(c);

        if (c.getContractID() > nextID)
            nextID = c.getContractID();
    }
    file.close();
}
Tenant *TenantRegistry::getTenantByID(int tenantID)
{
    for (Tenant &t : tenants)
    {
        if (tenantID == t.getTenantID())
        {
            return &t;
        }
    }
    return nullptr;
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

vector<int> PropertyRegistry::getAllPropertiesID()
{
    vector<int> res;
    for (Property &p : properties)
    {
        res.push_back(p.getPropertyID());
    }
    return res;
}

bool PropertyRegistry::removePropertyByID(int id)
{
    for (int i = 0; i < properties.size(); i++)
    {
        if (properties[i].getPropertyID() == id)
        {
            properties.erase(properties.begin() + i);
            return true;
        }
    }
    return false;
}

bool PropertyRegistry::listProperty(int id)
{
    for (int i = 0; i < properties.size(); i++)
    {
        if (properties[i].getPropertyID() == id)
        {
            properties[i].setIsListed(true);
            return true;
        }
    }
    return false;
}

bool PropertyRegistry::delistProperty(int id)
{
    for (int i = 0; i < properties.size(); i++)
    {
        if (properties[i].getPropertyID() == id)
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
    int tempArea = prop->getArea();
    int tempRentalValue = prop->getRentalValue();
    return {tempLocation, tempType, tempDesc, to_string(tempRentalValue), to_string(tempArea), to_string(id)};
}
void PropertyRegistry::saveToFile()
{
    _mkdir("data");
    ofstream file("data/property.txt");
    for (Property p : properties)
    {
        file
            << p.getPropertyID() << ","
            << p.getOwnerID() << ","
            << p.getTenantID() << ","
            << p.getIsListed() << ","
            << p.getIsRented() << ","
            << p.getType() << ","
            << p.getLocation() << ","
            << p.getDescription() << ","
            << p.getArea() << ","
            << p.getRentalValue() << ","
            << p.getMaintenanceStatus()
            << endl;
    }

    file.close();
}
void PropertyRegistry::loadFromFile()
{
    ifstream file("data/property.txt");

    if (!file.is_open())
        return;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        vector<string> data;
        string value;

        while (getline(ss, value, ','))
        {
            data.push_back(value);
        }

        if (data.size() < 11)
            continue;

        Property p(
            stoi(data[1]), // ownerID
            stoi(data[2]), // tenantID
            stoi(data[3]), // isListed
            stoi(data[4]), // isRented
            data[5],       // type
            data[6],       // location
            data[7],       // description
            stoi(data[8]), // area
            stoi(data[9]), // rentalValue
            data[10]       // maintenance
        );

        p.setPropertyID(stoi(data[0]));

        properties.push_back(p);
    }

    file.close();
}
