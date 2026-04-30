#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Property {
private:
    string name;
    int propertyID;
    string type;
    string location;
    vector<double> dimensions; // length and width for simplicity
    double rentalValue;
public:
    Property(string name, int propertyID, string type, string location, vector<double> dimensions, double rentalValue) : name(name), propertyID(propertyID), type(type), location(location), dimensions(dimensions), rentalValue(rentalValue) {}

    string getName() const { return name; }
    int getPropertyID() const { return propertyID; }
    string getType() const { return type; }
    string getLocation() const { return location; }
    vector<double> getDimensions() const { return dimensions; }
    double getRentalValue() const { return rentalValue; }

    void setName(string newName) { name = newName; }
    void setPropertyID(int newPropertyID) { propertyID = newPropertyID; }
    void setType(string newType) { type = newType; }
    void setLocation(string newLocation) { location = newLocation; }
    void setRentalValue(double newRentalValue) { rentalValue = newRentalValue; }
};


class Owner {
private:
    string name;
    string password;
    vector<Property> properties;
public:
    Owner(string name, string password) : name(name), password(password) {}
    
    string getName() const { return name; }
    vector<Property> getProperties() const { return properties; }

    void setName(string newName) { name = newName; }

    void addProperty(const Property& property);
};

#endif // PROPERTY_H