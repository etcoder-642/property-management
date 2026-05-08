#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/property.h"

using namespace std;

void Owner::addProperty(const int& propertyID){
    propertyIDs.push_back(propertyID);
}

void Owner::removeProperty(const int& propertyID)
{
    propertyIDs.erase(remove(propertyIDs.begin(), propertyIDs.end(), propertyID), propertyIDs.end());
}