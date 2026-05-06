#include <iostream>
#include <string>
#include <vector>

#include "../include/display.h"
#include "../include/property.h"
#include "../include/registry.h"

using namespace std;

void handleOwnerSession(Owner &owner)
{
    int ownerChoice = 0;
    while(ownerChoice != 5) {
        ownerChoice = getOwnerSessionMenu(owner);
        switch (ownerChoice)
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

void handleRegister(int registerChoice, OwnerRegistry &ownerRegistry)
{
    if (registerChoice == 1)
    {
        vector<string> ownerInfo = handleOwnerRegistry();
        Owner newOwner(ownerInfo[0], ownerInfo[1]);
        ownerRegistry.addOwner(newOwner);
        displaySuccessMessage("Owner registered successfully!");
        handleOwnerSession(newOwner);
    }
    else if (registerChoice == 2)
    {
    }
}

void handleAdmin()
{
}

void routeMainMenuChoice(int choice, OwnerRegistry &ownerRegistry)
{
    switch (choice)
    {
    case 1:
    {
        int loginChoice = handleLoginUI();
        if(loginChoice == 3) return; // Back to main menu
        handleLogin(loginChoice);
    }
    break;
    case 2:
    {
        int registerChoice = handleRegisterUI();
        if(registerChoice == 3) return; // Back to main menu
        handleRegister(registerChoice, ownerRegistry);
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
    OwnerRegistry ownerRegistry;
    int choice;
    while (choice != 5)
    {
        choice = initialPage();
        routeMainMenuChoice(choice, ownerRegistry);
    }
}