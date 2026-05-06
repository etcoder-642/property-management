#include <iostream>
#include <string>
#include <vector>

#include "../include/property.h"

using namespace std;

void Owner::addProperty(const int& propertyID){
    propertyIDs.push_back(propertyID);
}
