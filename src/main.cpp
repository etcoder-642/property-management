#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
    while (choice != 5)
    {
        choice = initialPage();
        routeMainMenuChoice(choice, registry);
    }
}