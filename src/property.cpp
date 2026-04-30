#include <iostream>
#include <string>
#include <vector>

#include "../include/property.h"

using namespace std;

void Owner::addProperty(const Property& property){
    properties.push_back(property);
}
