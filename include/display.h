#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>

#include "../include/property.h"
#include "../include/registry.h"

using namespace std;

int initialPage();
vector<string> handleOwnerRegistry();
void printBox(string title, int width);
void clearScreen();
int handleLoginUI();
int handleRegisterUI();
void displaySuccessMessage(string message);
int getOwnerSessionMenu(Owner &owner);
void pause();
#endif