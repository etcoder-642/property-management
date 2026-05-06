#include <iostream>
#include <string>
#include <vector>

#include "../include/display.h"
#include "../include/property.h"
#include "../include/registry.h"

using namespace std;

vector<string> splitString(string input, char identifier)
{
    string section = "";
    vector<string> res;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == identifier)
        {
            if(!section.empty()) res.push_back(section);
            section = "";
        }
        else
        {
            section += input[i];
        }
    }
    if(!section.empty()) res.push_back(section); 
    return res;
}

void handleMyPropertiesSession(Owner &owner)
{
    int myPropertiesChoice = 0;
    while (myPropertiesChoice != 7)
    {
        myPropertiesChoice = getMyPropertiesSession();
        switch (myPropertiesChoice)
        {
        case 1:
            // View Properties
            break;
        case 2:
        {
            vector<string> newPropertyInfo = newPropertyForm();
            vector<string> dimensionsStr = splitString(newPropertyInfo[3], ' ');
            vector<double> dimensions = {stod(dimensionsStr[0]), stod(dimensionsStr[1])};
            Property newProperty(-1, -1, false, false, newPropertyInfo[0], newPropertyInfo[1], newPropertyInfo[2], dimensions, stod(newPropertyInfo[4]));
            owner.addProperty(newProperty);
            displaySuccessMessage("Property added successfully!");
            pause();
        }
            break;
        case 3:
            // Remove Properties
            break;
        case 4:
            // Edit Property
            break;
        case 5:
            // List Properties
            break;
        case 6:
            // UnList Properties
            break;
        default:
            break;
        }
    }
}

void handleOwnerSession(Owner &owner)
{
    int ownerChoice = 0;
    while (ownerChoice != 6)
    {
        ownerChoice = getOwnerSessionMenu(owner);
        switch (ownerChoice)
        {
        case 1:
        {
            handleMyPropertiesSession(owner);
        }
            break;
        case 2:
            // Add Property
            break;
        case 3:
            // Edit Property
            break;
        case 4:
            // View Tenants
            break;
        default:
            break;
        }
    }
}

void handleTenantSession(Tenant &tenant)
{
    int tenantChoice = 0;
    while (tenantChoice != 6)
    {
        tenantChoice = getTenantSessionMenu(tenant  );
        switch (tenantChoice)
        {
        case 1:
            // View Properties
            break;
        case 2:
            // Add Property
            break;
        case 3:
            // Edit Property
            break;
        case 4:
            // View Tenants
            break;
        default:
            break;
        }
    }
}

void handleLogin(int loginChoice)
{
    if (loginChoice == 1)
    {
    }
    else if (loginChoice == 2)
    {
    }
}

void handleRegister(int registerChoice, OwnerRegistry &ownerRegistry, TenantRegistry &tenantRegistry)
{
    if (registerChoice == 1)
    {
        vector<string> ownerInfo = displayRegistry(1);
        Owner newOwner(ownerInfo[0], ownerInfo[1], ownerInfo[2]);
        ownerRegistry.addOwner(newOwner);
        displaySuccessMessage("Owner registered successfully!");
        pause();
        handleOwnerSession(newOwner);
    }
    else if (registerChoice == 2)
    {
        vector<string> tenantInfo = displayRegistry(2);
        Tenant newTenant(tenantInfo[0], tenantInfo[1], tenantInfo[2]);
        tenantRegistry.addTenant(newTenant);
        displaySuccessMessage("Tenant registered successfully!");
        pause();
        handleTenantSession(newTenant);
    }
}

void handleAdmin()
{
}

void routeMainMenuChoice(int choice, OwnerRegistry &ownerRegistry, TenantRegistry &tenantRegistry)
{
    switch (choice)
    {
    case 1:
    {
        int loginChoice = handleLoginUI();
        if (loginChoice == 3)
            return; // Back to main menu
        handleLogin(loginChoice);
    }
    break;
    case 2:
    {
        int registerChoice = handleRegisterUI();
        if (registerChoice == 3)
            return; // Back to main menu
        handleRegister(registerChoice, ownerRegistry, tenantRegistry);
    }
    break;
    case 3:
    {
        handleAdmin();
    }
    break;
    default:
        break;
    }
}


int main()
{
    TenantRegistry tenantRegistry;
    OwnerRegistry ownerRegistry;
    int choice;
    while (choice != 5)
    {
        choice = initialPage();
        routeMainMenuChoice(choice, ownerRegistry, tenantRegistry);
    }
}