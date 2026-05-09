#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include "property.h"

using namespace std;

class OwnerRegistry {
private:
    vector<Owner> owners;
    int nextID = 0;
public:
    OwnerRegistry() {}

    vector<Owner>& getOwners() { return owners; }
    int addOwner(Owner& owner);
    Owner* verifyData(vector<string> input);
};

class TenantRegistry {
private:
   vector<Tenant> tenants;
   int nextID = 0;
public:
   TenantRegistry() {}

   vector<Tenant>& getTenants() { return tenants; }

   Tenant* getTenantByID(int tenantID);
   int addTenant(Tenant& tenant);
   Tenant* verifyData(vector<string> input);
};

class PropertyRegistry {
private:
    vector<Property> properties;
    int nextID = 0;
public:
    PropertyRegistry() {}

    int addProperty(Property& property);
    vector<Property> getProperties() const { return properties; };
    Property* getPropertyByID(int propertyID);
    vector<int> getAllPropertiesID();

    bool removePropertyByID(int id);
    vector<string> getFormattedPropertyData(int id);
    bool listProperty(int id);
    bool delistProperty(int id);
};

class ContractRegistry {
private:
    vector<Contract> contracts;
    int nextID = 0;
public:
    ContractRegistry() {}
    vector<Contract> getContracts() const {return contracts; }
    Contract* getContractByID(int contractID);
    bool activateContractByID(int contractID);

    int addContract(Contract& contract);
};

struct AppRegistry {
    OwnerRegistry ownerRegistry;
    TenantRegistry tenantRegistry;
    PropertyRegistry propertyRegistry;
    ContractRegistry contractRegistry;
};

#endif // REGISTRY_H