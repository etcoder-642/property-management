#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>

#include "../include/property.h"
#include "../include/registry.h"

using namespace std;

int initialPage();
vector<string> displayRegistry(int registerChoice);
void printBox(string title, int width);
void clearScreen();
int handleLoginUI();
int handleRegisterUI();
void displaySuccessMessage(string message);
int getOwnerSessionMenu(Owner &owner);
int getTenantSessionMenu(Tenant &tenant);
int getMyPropertiesSession();
vector<string> newPropertyForm();
void displayProperty(vector<string> propertyInfo);
void displayPropertyHeader(vector<string> propertyHeader);
void pause();
#endif