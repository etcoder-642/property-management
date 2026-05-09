#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "../include/session.h"
#include "../include/property.h"
#include "../include/registry.h"
#include "../include/display.h"

using namespace std;

// helper function: checks for existence of an integer in an array. Returns true if value is found either it turns false.
bool checkValueExistence(int i, vector<int> arr)
{
    for (int a : arr)
    {
        if (a == i)
        {
            return true;
            break;
        }
    }
    return false;
}

// help function: it splits string into arrays using an identifier. e.g. splitString("Hi.there.min", '.') => {"Hi", "there", "min"}
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

// helper function: It takes an owner class and the main registry and it lists all displays all properties owned by that owner
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
            clearScreen();
            displayHeader("PROPERTY LIST");
            // list all Properties
            listOwnerProperties(owner, registry);
            pause();
        }
        break;
        case 2: // Add New Properties
        {
            clearScreen();
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
            clearScreen();
            displayHeader("REMOVE PROPERTY");
            displayInfo("Enter 0 to go back");
            displaySubHeader("Choose the property you want to remove by entering the number: ");
            // list properties for the user to chose which to remove
            listOwnerProperties(owner, registry);
            // get which property to remove
            int propertyToBeRemoved = receiveData();
            if(propertyToBeRemoved == 0) break;
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
            clearScreen();
            // Display properties to choose from
            displayHeader("EDIT PROPERTY");
            displaySubHeader("Choose the property you want to edit: ");
            displayInfo("Enter 0 to go back");
            listOwnerProperties(owner, registry);

            // Get which property to edit
            int propertyToEdit = receiveData();
            if (propertyToEdit == 0)
                break;
            if (!checkValueExistence(propertyToEdit, registry.propertyRegistry.getAllPropertiesID()))
            {
                displayErrorMessage("Invalid Input!");
                pause();
                break;
            }
            Property *prop = registry.propertyRegistry.getPropertyByID(propertyToEdit);
            if (prop == nullptr)
            {
                displayErrorMessage("Property not found!");
                pause();
                break;
            }

            // clear the screen for the next session
            clearScreen();
            // display the current values
            displayHeader("CURRENT VALUES");
            displayKeyValue("Current Type", prop->getType());
            displayKeyValue("Current Location", prop->getLocation());
            displayKeyValue("Current Description", prop->getDescription());
            displayKeyValue("Current Area", to_string(prop->getArea()));
            displayKeyValue("Current Rental Value", to_string(prop->getRentalValue()));
            // take the new values
            vector<string> newPropertyInfo = newPropertyForm();
            prop->setType(newPropertyInfo[0]);
            prop->setLocation(newPropertyInfo[1]);
            prop->setDescription(newPropertyInfo[2]);
            prop->setArea(stoi(newPropertyInfo[3]));
            prop->setRentalValue(stoi(newPropertyInfo[4]));

            displaySuccessMessage("Property updated successfully!");
            pause();
        }
        break;
        case 5: // List Properties
        {
            clearScreen();
            displayHeader("LIST A PROPERTY");
            displaySubHeader("Choose a property you want to list: ");
            displayInfo("Enter 0 to go back");
            // list properties for the user to chose which to remove
            listOwnerProperties(owner, registry);
            // take the value the user wants to list
            int propertyToBeListed = receiveData();
            if(propertyToBeListed == 0) break;
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
            clearScreen();
            displayHeader("DELIST A PROPERTY");
            displaySubHeader("Choose a property you want to delist");
            displayInfo("Enter 0 to go back");
            // list properties for the user to chose which to remove
            listOwnerProperties(owner, registry);
            // take the value the user wants to list
            int propertyToBeDelisted = receiveData();
            if(propertyToBeDelisted == 0) break;
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
        tenantChoice = getTenantLeaseSession();
        switch (tenantChoice)
        {
        case 1: // View Current Lease
        {
            clearScreen();
            displayHeader("MY CURRENT LEASE");
            vector<Contract> allContracts = registry.contractRegistry.getContracts();
            Contract *activeContract = nullptr;
            for (int i = 0; i < allContracts.size(); i++)
            {
                if (allContracts[i].getTenantID() == tenant.getTenantID() && allContracts[i].getIsActive())
                {
                    activeContract = registry.contractRegistry.getContractByID(allContracts[i].getContractID());
                    break;
                }
            }
            if (activeContract == nullptr)
            {
                displayValue("You have no active lease.");
                displayEndLine();
                pause();
                break;
            }
            Property *prop = registry.propertyRegistry.getPropertyByID(activeContract->getPropertyID());
            Date d = activeContract->getDate();
            displayKeyValue("Property", prop->getType() + " at " + prop->getLocation());
            displayKeyValue("Rental Amount", to_string(activeContract->getRentalAmount()) + " ETB/month");
            displayKeyValue("Move-in Date", to_string(d.day) + "/" + to_string(d.month) + "/" + to_string(d.year));
            displayKeyValue("Duration", to_string(activeContract->getContractDuration()) + " months");
            displayKeyValue("Status", "ACTIVE");
            displayEndLine();
            pause();
        }
        break;
        case 2: // Pay Rent
        {
            clearScreen();
            displayHeader("PAY RENT");
            vector<Contract> allContracts = registry.contractRegistry.getContracts();
            Contract *activeContract = nullptr;
            for (int i = 0; i < allContracts.size(); i++)
            {
                if (allContracts[i].getTenantID() == tenant.getTenantID() && allContracts[i].getIsActive())
                {
                    activeContract = registry.contractRegistry.getContractByID(allContracts[i].getContractID());
                    break;
                }
            }
            if (activeContract == nullptr)
            {
                displayErrorMessage("You have no active lease to pay for.");
                pause();
                break;
            }
            Property *prop = registry.propertyRegistry.getPropertyByID(activeContract->getPropertyID());
            displayKeyValue("Property", prop->getType() + " at " + prop->getLocation());
            displayKeyValue("Amount Due", to_string(activeContract->getRentalAmount()) + " ETB");
            displayEndLine();
            displaySubHeader("Press 1 to confirm payment or 0 to cancel: ");
            int confirm = receiveData();
            if (confirm == 1)
                displaySuccessMessage("Payment of " + to_string(activeContract->getRentalAmount()) + " ETB submitted successfully!");
            else
                displayErrorMessage("Payment cancelled.");
            pause();
        }
        break;
        }
    }
}

    void handleOwnerSession(Owner & owner, AppRegistry & registry)
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
            {
                clearScreen();
                displayHeader("APPLICATIONS IN PROGRESS");
                displaySubHeader("Enter the application number you want to approve: ");
                displayInfo("Enter 0 to go back");
                vector<Contract> allContracts = registry.contractRegistry.getContracts();
                vector<int> contractsApplied;
                for (int i = 0; i < allContracts.size(); i++)
                {
                    if (allContracts[i].getOwnerID() == owner.getOwnerID() && !allContracts[i].getIsActive())
                    {
                        contractsApplied.push_back(allContracts[i].getContractID());
                    }
                }
                for (int i = 0; i < contractsApplied.size(); i++)
                {
                    Contract *contr = registry.contractRegistry.getContractByID(contractsApplied[i]);
                    int propertyID = contr->getPropertyID();
                    int tenantID = contr->getTenantID();
                    Tenant *tent = registry.tenantRegistry.getTenantByID(tenantID);
                    Property *prop = registry.propertyRegistry.getPropertyByID(propertyID);

                    string str = "[" + to_string(contractsApplied[i]) + "] " + prop->getType() + " located at " + prop->getLocation() + " | " + "Tenant: " + tent->getName() + " | PENDING";
                    displayValue(str);
                    displayEndLine();
                }
                int applicationToApprove = receiveData();
                if(applicationToApprove == 0){break;}
                if(!checkValueExistence(applicationToApprove, contractsApplied))
                {
                    displayErrorMessage("Invalid Selection!");
                    pause();
                    break;
                }
                registry.contractRegistry.activateContractByID(applicationToApprove);
                displaySuccessMessage("Application Approved Successfully!");
                pause();
            }
            break;
            case 3: // View Contracts
            {
                clearScreen();
                displayHeader("ACTIVE CONTRACTS");
                vector<Contract> allContracts = registry.contractRegistry.getContracts();
                vector<int> activeContracts;
                for (int i = 0; i < allContracts.size(); i++)
                {
                    if (allContracts[i].getOwnerID() == owner.getOwnerID())
                    {
                        activeContracts.push_back(allContracts[i].getContractID());
                    }
                }
                for (int i = 0; i < activeContracts.size(); i++)
                {
                    Contract *contr = registry.contractRegistry.getContractByID(activeContracts[i]);
                    int propertyID = contr->getPropertyID();
                    int tenantID = contr->getTenantID();
                    Tenant *tent = registry.tenantRegistry.getTenantByID(tenantID);
                    Property *prop = registry.propertyRegistry.getPropertyByID(propertyID);

                    string str = "[" + to_string(activeContracts[i]) + "] " + prop->getType() + " located at " +
                                 prop->getLocation() + " | Tenant: " + tent->getName() + " | " + to_string(prop->getRentalValue()) +
                                 " ETB/month | Duration: " + to_string(contr->getContractDuration());
                    displayValue(str);
                    displayEndLine();
                }
                pause();
            }
            break;
            case 4: // Update Profile
            {
                clearScreen();
                displayHeader("UPDATE PROFILE");
                displaySubHeader("Enter Values to update your profile: ");
                // display current values
                displayKeyValue("Current Registered Name", owner.getName());
                displayKeyValue("Current Password", owner.getPassword());

                vector<string> updatedInfo = displayRegistry();
                owner.setName(updatedInfo[0]);
                owner.setPassword(updatedInfo[1]);
                displaySuccessMessage("Profile updated successfully!");
                pause();
            }
            break;
            default:
                break;
            }
        }
    }

    void handleTenantSession(Tenant & tenant, AppRegistry & registry)
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
                // 1. Setup the Visuals
                displayHeader("LISTED PROPERTIES");
                displaySubHeader("Choose a property you want to apply to: ");

                // get every property in the system first.
                vector<Property> allProperties = registry.propertyRegistry.getProperties();
                vector<int> listedProperties;

                // loop through all properties to find only the ones the Owners have "Listed" for rent.
                for (int i = 0; i < allProperties.size(); i++)
                {
                    if (allProperties[i].getIsListed())
                    {
                        listedProperties.push_back(allProperties[i].getPropertyID());
                    }
                }
                // loop through listedProperties list of IDs and display them to the Tenant.
                for (int i = 0; i < listedProperties.size(); i++)
                {
                    // format the raw data into a readable string for the screen.
                    vector<string> propertiesInfo = registry.propertyRegistry.getFormattedPropertyData(listedProperties[i]);
                    displayProperty(stoi(propertiesInfo[5]), propertiesInfo);
                }

                // The Tenant types in, the ID of the property they want to rent.
                int propertyApplied = receiveData();
                //  check if the ID the user typed is actually one of the properties showed to them.
                // If the ID isn't in our "Listed" list, we stop and show an error
                if (!checkValueExistence(propertyApplied, listedProperties))
                {
                    displayErrorMessage("Invalid selection!");
                    pause();
                    break;
                }

                // The Application Process
                displayHeader("PROPERTY APPLICATION");
                displaySubHeader("Enter necessary information to the property you are applying to: ");

                // Collect details like move-in date and duration from the user.
                vector<string> applicationInfo = propertyApplicationForm();
                // We split the date (Ex: 12/05/2026) into day, month, and year.
                vector<string> dateInString = splitString(applicationInfo[0], '/');
                Date moveInDate = {stoi(dateInString[0]), stoi(dateInString[1]), stoi(dateInString[2])};

                // find the specific property the user picked.
                Property *prop = registry.propertyRegistry.getPropertyByID(propertyApplied);
                // create a new Contract object to link the Owner, the Tenant, and the Property together.
                Contract newContract(prop->getOwnerID(), tenant.getTenantID(), propertyApplied, moveInDate, prop->getRentalValue(), stoi(applicationInfo[1]));

                // make the application "Pending" (Inactive) until the Owner approves it.
                newContract.setIsActive(false);
                // add the data to ContractRegistry for storage purposes.
                registry.contractRegistry.addContract(newContract);
                displaySuccessMessage("Your Application have been successfully submitted.");
                displaySuccessMessage("You will be notified once the owner reviews it.");
                pause();
            }
            break;
            case 3: // My Applications
            {
                clearScreen();
                displayHeader("MY APPLICATIONS");
                vector<Contract> allContracts = registry.contractRegistry.getContracts();
                vector<int> myContracts;
                for (int i = 0; i < allContracts.size(); i++)
                {
                    if (allContracts[i].getTenantID() == tenant.getTenantID())
                    {
                        myContracts.push_back(allContracts[i].getContractID());
                    }
                }
                for (int i = 0; i < myContracts.size(); i++)
                {
                    Contract *contr = registry.contractRegistry.getContractByID(myContracts[i]);
                    Property *prop = registry.propertyRegistry.getPropertyByID(contr->getPropertyID());
                    string status = contr->getIsActive() ? "APPROVED" : "PENDING";
                    string str = "[" + to_string(myContracts[i]) + "] " + prop->getType() + " located at " +
                                 prop->getLocation() + " | " + to_string(prop->getRentalValue()) +
                                 " ETB/month | " + status;
                    displayValue(str);
                    displayEndLine();
                }
                pause();
            }
            break;
            case 4: // Update Profile
            {
                clearScreen();
                displayHeader("UPDATE PROFILE");
                displaySubHeader("Enter Values to update your profile: ");
                // display current values
                displayKeyValue("Current Registered Name", tenant.getName());
                displayKeyValue("Current Password", tenant.getPassword());

                vector<string> updatedInfo = displayRegistry();
                tenant.setName(updatedInfo[0]);
                tenant.setPassword(updatedInfo[1]);
                displaySuccessMessage("Profile updated successfully!");
                pause();
            }
            break;
            default:
                break;
            }
        }
    }

    void handleLogin(int loginChoice, AppRegistry &registry)
    {
        if (loginChoice == 1)
        {
            clearScreen();
            displayHeader("OWNER LOGIN PAGE");
            vector<string> ownerInfo = displayRegistry();
            Owner *ownerPtr = registry.ownerRegistry.verifyData(ownerInfo);
            if (ownerPtr)
            {
                displaySuccessMessage("Login Successful!");
                pause();
                handleOwnerSession(*ownerPtr, registry);
            }
            else
            {
                displayErrorMessage("Login Failed!");
                pause();
            }
        }
        else if (loginChoice == 2)
        {
            clearScreen();
            displayHeader("TENANT LOGIN PAGE");
            vector<string> tenantInfo = displayRegistry();
            Tenant *tenantPtr = registry.tenantRegistry.verifyData(tenantInfo);
            if (tenantPtr)
            {
                displaySuccessMessage("Login Successful!");
                pause();
                handleTenantSession(*tenantPtr, registry);
            }
            else
            {
                displayErrorMessage("Login Failed!");
                pause();
            }
        }
    }

    void handleRegister(int registerChoice, AppRegistry &registry)
    {
        if (registerChoice == 1)
        {
            clearScreen();
            displayHeader("OWNER REGISTRATION PAGE");
            vector<string> ownerInfo = displayRegistry();
            Owner tempOwner(ownerInfo[0], ownerInfo[1]);
            registry.ownerRegistry.addOwner(tempOwner);
            int index = registry.ownerRegistry.getOwners().size() - 1;
            displaySuccessMessage("Owner registered successfully!");
            pause();
            handleOwnerSession(registry.ownerRegistry.getOwners()[index], registry);
        }
        else if (registerChoice == 2)
        {
            clearScreen();
            displayHeader("TENANT REGISTRATION PAGE");
            vector<string> tenantInfo = displayRegistry();
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
            handleLogin(loginChoice, registry);
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
