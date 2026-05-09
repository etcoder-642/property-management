#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Property {
private:
    int propertyID;
    int ownerID;
    int tenantID; // will be -1 if vacant

    bool isListed;
    bool isRented;

    string type; // villa, town house etc.
    string location; // city name, neighbourhood Example: Addis Ababa, Bole
    string description; // additional info
    int area; // length and width for simplicity
    int rentalValue;
    string maintenanceStatus;
public:
    Property(int ownerID, int tenantID, bool isListed, bool isRented, string type, string location, string description, int area, int rentalValue, string maintenanceStatus)
     : ownerID(ownerID), tenantID(tenantID), isListed(isListed), isRented(isRented), type(type), location(location), description(description), area(area), rentalValue(rentalValue), maintenanceStatus(maintenanceStatus), propertyID(-1) {}

    int getPropertyID() const { return propertyID; }
    int getOwnerID() const { return ownerID; }
    int getTenantID() const { return tenantID; }
    string getType() const { return type; }
    string getLocation() const { return location; }
    string getDescription() const { return description; }
    int getArea() const { return area; }
    int getRentalValue() const { return rentalValue; }
    string getMaintenanceStatus() const { return maintenanceStatus; }
    bool getIsListed() const {return isListed; }
    bool getIsRented() const {return isRented; }

    void setPropertyID(int newPropertyID) { propertyID = newPropertyID; }
    void setOwnerID(int newOwnerID) { ownerID = newOwnerID; }
    void setTenantID(int newTenantID) { tenantID = newTenantID; }
    void setType(string newType) { type = newType; }
    void setLocation(string newLocation) { location = newLocation; }
    void setDescription(string newDescription) { description = newDescription; }
    void setRentalValue(int newRentalValue) { rentalValue = newRentalValue; }
    void setArea(int newArea) {area = newArea; }
    void setMaintenanceStatus(string newMS) { maintenanceStatus = newMS;}
    void setIsListed(bool value) { isListed = value; }
    void setIsRented(bool value) { isRented = value; }
};


class Owner {
private:
    int ownerID;
    string name;
    string password;
    vector<int> propertyIDs;
public:
    Owner(string name, string password)
     : name(name), password(password), ownerID(-1) {}
    
    int getOwnerID() const { return ownerID; }
    string getName() const { return name; }
    string getPassword() const { return password; }
    vector<int> getPropertyIDs() const { return propertyIDs; }

    void setName(string newName) { name = newName; }
    void setPassword(string newPassword) { password = newPassword; }
    void setOwnerID(int newOwnerID) { ownerID = newOwnerID; }

    void addProperty(const int& propertyID);
    void removeProperty(const int& propertyID);
};

class Tenant {
private:
    int tenantID;
    string name;
    string password;
public:
    Tenant(string name, string password)
     : name(name), password(password), tenantID(-1) {}
    
    int getTenantID() const { return tenantID; }
    string getName() const { return name; }
    string getPassword() const { return password; }

    void setName(string newName) { name = newName; }
    void setPassword(string nP) { password = nP; }
    void setTenantID(int newTenantID) { tenantID = newTenantID; }
};

struct Date {
    int day;
    int month;
    int year;
};

class Contract {
private:
    int contractID;
    int ownerID;
    int tenantID;
    int propertyID;

    bool isActive; // to check if the contract have been approved by the owner or not.

    Date date;
    double rentalAmount;
    int contractDuration; // in months
public:
    Contract(int ownerID, int tenantID, int propertyID, Date date, double rentalAmount, int contractDuration)
     : ownerID(ownerID), tenantID(tenantID), propertyID(propertyID), date(date), 
       rentalAmount(rentalAmount), contractDuration(contractDuration), contractID(-1) {}

    int getContractID() const { return contractID; }
    int getOwnerID() const { return ownerID; }
    int getTenantID() const { return tenantID; }
    int getPropertyID() const { return propertyID; }
    Date getDate() const { return date; }
    double getRentalAmount() const { return rentalAmount; }
    int getContractDuration() const { return contractDuration; }
    bool getIsActive() const { return isActive; }

    void setContractID(int newContractID) { contractID = newContractID; }
    void setDate(Date newDate) { date = newDate; }
    void setRentalAmount(double newRentalAmount) { rentalAmount = newRentalAmount; }
    void setContractDuration(int newContractDuration) { contractDuration = newContractDuration; }
    void setIsActive(bool value) {isActive = value; }
};

#endif // PROPERTY_H