#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>

#include "../include/property.h"
#include "../include/registry.h"

using namespace std;

// special functions to clear screen and pause code execution
void clearScreen();
void pause();

// Functions for display of different section of an interface (title, heading, subheading and main content)
void displayHeader(string str);
void displaySubHeader(string str);
void displayValue(string str);
void displayInfo(string str);
void displayEndLine();
void displayKeyValue(string str, string subStr);
void displayProperty(int num, vector<string> propertyInfo);

// Function for display of different message
void displaySuccessMessage(string message);
void displayErrorMessage(string message);

// Functions that handle log in and registration
vector<string> displayRegistry();
int handleLoginUI();
int handleRegisterUI();

// Functions that handle different sessions and interfaces
int initialPage();
int getOwnerSessionMenu(Owner &owner);
int getTenantSessionMenu(Tenant &tenant);
int getMyPropertiesSession();
int getTenantLeaseSession();

// function to receive data from the user using `getline()`
int receiveData();
vector<string> newPropertyForm();
vector<string> propertyApplicationForm();

#endif