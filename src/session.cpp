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

void listOwnerProperties(Owner &owner, AppRegistry &registry)
{
    vector<int> properties = owner.getPropertyIDs();
    for (int i = 0; i < properties.size(); i++)
    {
        vector<string> propertiesInfo = registry.propertyRegistry.getFormattedPropertyData(properties[i]);
        displayProperty(properties[i], propertiesInfo);
    }
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
            displayHeader("PROPERTY LIST");
            // list all Properties
            listOwnerProperties(owner, registry);
            pause();
        }
        break;
        case 2: // Add New Properties
        {
            vector<string> newPropertyInfo = newPropertyForm();
            int ownerID = owner.getOwnerID();
            Property newProperty(ownerID, -1, false, false, newPropertyInfo[0], newPropertyInfo[1], newPropertyInfo[2], stoi(newPropertyInfo[3]), stoi(newPropertyInfo[4]), "Good");
            int id = registry.propertyRegistry.addProperty(newProperty);
            owner.addProperty(id);
            displaySuccessMessage("Property added successfully!");
            pause();
        }
        break;
        case 3: // Remove Properties
        {
            displayHeader("REMOVE PROPERTY");
            displaySubHeader("Choose the property you want to remove by entering the number: ");
            // list properties for the user to chose which to remove
            listOwnerProperties(owner, registry);
            // get which property to remove
            int propertyToBeRemoved = receiveData();
            if (registry.propertyRegistry.removePropertyByID(propertyToBeRemoved))
            {
                owner.removeProperty(propertyToBeRemoved);
                displaySuccessMessage("Property removed successfully");
            }
            else
                displayErrorMessage("Property removal failed!");
            pause();
        }
        break;
        case 4: // Edit Property
        {
            // Display properties to choose from
            displayHeader("EDIT PROPERTY");
            displaySubHeader("Choose the property you want to edit: ");
            listOwnerProperties(owner, registry);

            // Get which property to edit
            int propertyToEdit = receiveData(); // reuse same input function
            Property *prop = registry.propertyRegistry.getPropertyByID(propertyToEdit);
            if (prop == nullptr)
            {
                displayErrorMessage("Property not found!");
                pause();
                break;
            }

            // Get new values
            vector<string> newPropertyInfo = newPropertyForm();
            prop->setType(newPropertyInfo[0]);
            prop->setLocation(newPropertyInfo[1]);
            prop->setDescription(newPropertyInfo[2]);
            prop->setRentalValue(stoi(newPropertyInfo[4]));

            displaySuccessMessage("Property updated successfully!");
            pause();
        }
        break;
        case 5: // List Properties
        {
            displayHeader("LIST A PROPERTY");
            displaySubHeader("Choose a property you want to list: ");
            // list properties for the user to chose which to remove
            listOwnerProperties(owner, registry);
            // take the value the user wants to list
            int propertyToBeListed = receiveData();
            // if listing successful show a successMessage if it failed show an Error message
            if (registry.propertyRegistry.listProperty(propertyToBeListed))
            {
                displaySuccessMessage("Property successfully listed!");
            }
            else
                displayErrorMessage("Property listing failed!");
            pause();
        }
        break;
        case 6: // Delist Properties
            {
                displayHeader("DELIST A PROPERTY");
                displaySubHeader("Choose a property you want to delist");
                // list properties for the user to chose which to remove
                listOwnerProperties(owner, registry);
                // take the value the user wants to list
                int propertyToBeDelisted = receiveData();
                // if delisting successful show a successMessage if it failed show an Error message
                if (registry.propertyRegistry.delistProperty(propertyToBeDelisted))
                {
                    displaySuccessMessage("Property successfully delisted!");
                }
                else
                    displayErrorMessage("Property delisting failed!");
                pause();
            }
            break;
        default:
            break;
        }
    }
}

void handleTenantLeaseSession(Tenant &tenant, AppRegistry &registry)
{
    int tenantChoice = 0;
    while (tenantChoice != 3)
    {
        tenantChoice = getMyPropertiesSession();
        switch (tenantChoice)
        {
        case 1: // View Current Lease
            break;
        case 2: // Pay Rent
            break;
        default:
            break;
        }
    }
}

void handleOwnerSession(Owner &owner, AppRegistry &registry)
{
    int ownerChoice = 0;
    while (ownerChoice != 5)
    {
        ownerChoice = getOwnerSessionMenu(owner);
        switch (ownerChoice)
        {
        case 1: // My Properties
        {
            handleMyPropertiesSession(owner, registry);
        }
        break;
        case 2: // Applications Inbox
            break;
        case 3: // View Contracts
            break;
        case 4: // Update Profile
            break;
        default:
            break;
        }
    }
}

void handleTenantSession(Tenant &tenant, AppRegistry &registry)
{
    int tenantChoice = 0;
    while (tenantChoice != 5)
    {
        tenantChoice = getTenantSessionMenu(tenant);
        switch (tenantChoice)
        {
        case 1: // My Lease & Pay Rent
        {
            handleTenantLeaseSession(tenant, registry);
        }
        break;
        case 2: // Browse New Properties
        {
            displayHeader("LISTED PROPERTIES");
            displaySubHeader("Choose a property you want to apply to: ");
            vector<Property> allProperties = registry.propertyRegistry.getProperties();
            vector<int> listedProperties;
            for (int i = 0; i < allProperties.size(); i++)
            {
                if (allProperties[i].getIsListed())
                {
                    listedProperties.push_back(allProperties[i].getPropertyID());
                }
            }
            for (int i = 0; i < listedProperties.size(); i++)
            {
                vector<string> propertiesInfo = registry.propertyRegistry.getFormattedPropertyData(listedProperties[i]);
                displayProperty(stoi(propertiesInfo[4]), propertiesInfo);
            }
            // take a user input of where the property the tenant is applying to rent
            int propertyApplied = receiveData();
            displayHeader("PROPERTY APPLICATION");
            displaySubHeader("Enter necessary information to the property you are applying to: ");
            vector<string> applicationInfo = propertyApplicationForm();
            vector<string> dateInString = splitString(applicationInfo[0], '/');
            Date moveInDate = {stoi(dateInString[0]), stoi(dateInString[1]), stoi(dateInString[2])};
            Property* prop = registry.propertyRegistry.getPropertyByID(propertyApplied);
            Contract newContract(prop->getOwnerID(), tenant.getTenantID(), propertyApplied, moveInDate, prop->getRentalValue(), stoi(applicationInfo[1]));
            newContract.setIsActive(false);
            registry.contractRegistry.addContract(newContract);

            displaySuccessMessage("Your Application have been successfully submitted.");
            displaySuccessMessage("You will be notified once the owner reviews it.");
            pause();
        }
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
        Owner tempOwner(ownerInfo[0], ownerInfo[1]);
        registry.ownerRegistry.addOwner(tempOwner);
        int index = registry.ownerRegistry.getOwners().size() - 1;
        displaySuccessMessage("Owner registered successfully!");
        pause();
        handleOwnerSession(registry.ownerRegistry.getOwners()[index], registry);
    }
    else if (registerChoice == 2)
    {
        vector<string> tenantInfo = displayRegistry(2);
        Tenant tempTenant(tenantInfo[0], tenantInfo[1]);
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
