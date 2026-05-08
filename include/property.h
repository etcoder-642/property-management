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
    double area; // length and width for simplicity
    double rentalValue;
    string maintenanceStatus;
public:
    Property(int ownerID, int tenantID, bool isListed, bool isRented, string type, string location, string description, double area, double rentalValue, string maintenanceStatus)
     : ownerID(ownerID), tenantID(tenantID), isListed(isListed), isRented(isRented), type(type), location(location), description(description), area(area), rentalValue(rentalValue), maintenanceStatus(maintenanceStatus), propertyID(-1) {}

    int getPropertyID() const { return propertyID; }
    int getOwnerID() const { return ownerID; }
    int getTenantID() const { return tenantID; }
    string getType() const { return type; }
    string getLocation() const { return location; }
    string getDescription() const { return description; }
    double getArea() const { return area; }
    double getRentalValue() const { return rentalValue; }
    string getMaintenanceStatus() const { return maintenanceStatus; }
    bool getIsListed() const {return isListed; }
    bool getIsRented() const {return isRented; }

    void setPropertyID(int newPropertyID) { propertyID = newPropertyID; }
    void setOwnerID(int newOwnerID) { ownerID = newOwnerID; }
    void setTenantID(int newTenantID) { tenantID = newTenantID; }
    void setType(string newType) { type = newType; }
    void setLocation(string newLocation) { location = newLocation; }
    void setDescription(string newDescription) { description = newDescription; }
    void setRentalValue(double newRentalValue) { rentalValue = newRentalValue; }
    void setArea(double newArea) {area = newArea; }
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
    vector<int> getPropertyIDs() const { return propertyIDs; }

    void setName(string newName) { name = newName; }
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

    void setName(string newName) { name = newName; }
    void setTenantID(int newTenantID) { tenantID = newTenantID; }
};

struct Date {
    int day;
    int month;
    int year;
};

class Contract {
private:
    string contractTitle;
    string contractDescription;

    int contractID;
    int ownerID;
    int tenantID;
    int propertyID;

    bool isActive; // is the contract currently active or has it expired/been terminated?

    Date date;
    double rentalAmount;
    int contractDuration; // in months
public:
    Contract(string contractTitle, string contractDescription, int ownerID, 
             int tenantID, int propertyID, Date date, double rentalAmount, int contractDuration)
     : contractTitle(contractTitle), contractDescription(contractDescription), 
       ownerID(ownerID), tenantID(tenantID), propertyID(propertyID), date(date), 
       rentalAmount(rentalAmount), contractDuration(contractDuration), contractID(-1) {}

    string getContractTitle() const { return contractTitle; }
    string getContractDescription() const { return contractDescription; }
    int getContractID() const { return contractID; }
    int getOwnerID() const { return ownerID; }
    int getTenantID() const { return tenantID; }
    int getPropertyID() const { return propertyID; }
    Date getDate() const { return date; }
    double getRentalAmount() const { return rentalAmount; }
    int getContractDuration() const { return contractDuration; }

    void setContractID(int newContractID) { contractID = newContractID; }
    void setContractTitle(string newContractTitle) { contractTitle = newContractTitle; }
    void setContractDescription(string newContractDescription) { contractDescription = newContractDescription; }
    void setDate(Date newDate) { date = newDate; }
    void setRentalAmount(double newRentalAmount) { rentalAmount = newRentalAmount; }
    void setContractDuration(int newContractDuration) { contractDuration = newContractDuration; }
};



#endif // PROPERTY_H