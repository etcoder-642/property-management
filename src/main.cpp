#include <iostream>
#include <string>
#include <vector>

#include "../include/display.h"
#include "../include/property.h"
#include "../include/registry.h"

using namespace std;

int main() {
    OwnerRegistry ownerRegistry;
    int userChoice;
    while(userChoice != 7){
        userChoice = initialPage();
        switch(userChoice){
            case 1:
            {

            }
            break;
            case 2:
            break;
            case 3:
            {
                Owner newOwner("",""); // Temporary initialization
                vector<string> ownerInfo = handleOwnerRegistry();
                newOwner = Owner(ownerInfo[0], ownerInfo[1]);
                ownerRegistry.addOwner(newOwner);
                displaySpecialMessage("Owner registered successfully!");
            }
            break;
            default:
            break;
        }
    }
}