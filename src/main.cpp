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
    int choice = 0;
    while (choice != 4)
    {
        choice = initialPage();
        routeMainMenuChoice(choice, registry);
    }
}