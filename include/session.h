#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <vector>
#include <string>

#include "../include/property.h"
#include "../include/registry.h"
#include "../include/display.h"

using namespace std;

void handleOwnerSession(Owner &owner, AppRegistry &registry);
void handleMyPropertiesSession(Owner &owner, AppRegistry &registry);
void handleTenantSession(Tenant &tenant, AppRegistry &registry);
void handleLogin(int loginChoice);
void handleRegister(int registerChoice, AppRegistry &registry);
void routeMainMenuChoice(int choice, AppRegistry &registry);
void handleAdmin();


#endif