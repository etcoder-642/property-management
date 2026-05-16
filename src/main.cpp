#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "../include/display.h"
#include "../include/property.h"
#include "../include/registry.h"
#include "../include/session.h"

using namespace std;
int main()
{
    AppRegistry registry;

    // Load all data from files when program starts
    registry.ownerRegistry.loadFromFile();
    registry.propertyRegistry.loadFromFile();
    registry.tenantRegistry.loadFromFile();
    registry.contractRegistry.loadFromFile();
    int choice = 0;
    while (choice != 4)
    {
        choice = initialPage();
        routeMainMenuChoice(choice, registry);
    }

    // Save all data to files when program exits
    registry.ownerRegistry.saveToFile();
    registry.propertyRegistry.saveToFile();
    registry.tenantRegistry.saveToFile();
    registry.contractRegistry.saveToFile();
    return 0;
}