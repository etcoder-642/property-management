#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "../include/session.h"
#include "../include/property.h"
#include "../include/registry.h"
#include "../include/display.h"

using namespace std;

vector<string> splitString(string input, char identifier)
{
    string section = "";
    vector<string> res;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == identifier)
        {
            if (!section.empty())
                res.push_back(section);
            section = "";
        }
        else
        {
            section += input[i];
        }
    }
    if (!section.empty())
        res.push_back(section);
    return res;
}

void handleMyPropertiesSession(Owner &owner, AppRegistry &registry)
{
    int myPropertiesChoice = 0;
    while (myPropertiesChoice != 7)
    {
        myPropertiesChoice = getMyPropertiesSession();
        switch (myPropertiesChoice)
        {
        case 1: // View Properties
            {
                vector<int> properties = owner.getPropertyIDs();
                displayPropertyHeader({"LOCATION", "TYPE", "DESCRIPTION", "RENTAL VALUE", "DIMENSIONS"});
                for (int i : properties)
                {
                    Property *prop = registry.propertyRegistry.getPropertyByID(i);
                    if (prop == nullptr)
                    {
                        cout << "here's the problem" << endl;
                        continue;
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
                    double tempRentalValue = registry.propertyRegistry.getPropertyByID(i)->getRentalValue();
                    displayProperty({tempLocation, tempType, tempDesc, to_string(tempRentalValue), tempDimensionStr});
                }
                pause();
            }
            break;
        case 2: // Add New Properties
        {
            vector<string> newPropertyInfo = newPropertyForm();
            vector<string> dimensionsStr = splitString(newPropertyInfo[3], ' ');
            vector<double> dimensions = {stod(dimensionsStr[0]), stod(dimensionsStr[1])};
            Property newProperty(-1, -1, false, false, newPropertyInfo[0], newPropertyInfo[1], newPropertyInfo[2], dimensions, stod(newPropertyInfo[4]));
            int id = registry.propertyRegistry.addProperty(newProperty);
            owner.addProperty(id);
            displaySuccessMessage("Property added successfully!");
            pause();
        }
        break;
        case 3: // Remove Properties
        {
            
        }
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

void handleOwnerSession(Owner &owner, AppRegistry &registry)
{
    int ownerChoice = 0;
    while (ownerChoice != 6)
    {
        ownerChoice = getOwnerSessionMenu(owner);
        switch (ownerChoice)
        {
        case 1:
        {
            handleMyPropertiesSession(owner, registry);
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

void handleTenantSession(Tenant &tenant, AppRegistry &registry)
{
    int tenantChoice = 0;
    while (tenantChoice != 6)
    {
        tenantChoice = getTenantSessionMenu(tenant);
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

void handleRegister(int registerChoice, AppRegistry &registry)
{
    if (registerChoice == 1)
    {
        vector<string> ownerInfo = displayRegistry(1);
        Owner tempOwner(ownerInfo[0], ownerInfo[1], ownerInfo[2]);
        registry.ownerRegistry.addOwner(tempOwner);
        int index = registry.ownerRegistry.getOwners().size() - 1;
        displaySuccessMessage("Owner registered successfully!");
        pause();
        handleOwnerSession(registry.ownerRegistry.getOwners()[index], registry);
    }
    else if (registerChoice == 2)
    {
        vector<string> tenantInfo = displayRegistry(2);
        Tenant tempTenant(tenantInfo[0], tenantInfo[1], tenantInfo[2]);
        registry.tenantRegistry.addTenant(tempTenant);
        int index = registry.tenantRegistry.getTenants().size() - 1;
        displaySuccessMessage("Tenant registered successfully!");
        pause();
        handleTenantSession(registry.tenantRegistry.getTenants()[index], registry);
    }
}

void handleAdmin()
{
}

void routeMainMenuChoice(int choice, AppRegistry &registry)
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
        handleRegister(registerChoice, registry);
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
