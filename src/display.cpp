#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int initialPage() {
    int userChoice;
    cout << string(100,'=') <<endl;
    cout << string(40,'=') << "PROPERTY MANAGEMENT SYSTEM" << string(40,'=') << endl;
    cout << "1. Log In as Property Owner" << endl;
    cout << "2. Log In as Tenant" << endl;
    cout << "3. Register as Property Owner" << endl;
    cout << "4. Register as Tenant" << endl;
    cout << "5. Log In as System Admin" << endl;
    cout << "6. About the System" << endl;
    cout << "7. Exit" << endl;
    cout << string(100,'-') << endl;
    cout << "Enter your choice: ";
    cin >> userChoice;
    return userChoice;
}

vector<string> handleOwnerRegistry() {
    cout << string(100,'=') << endl;
    cout << "Owner Registration Page" << endl;
    cout << string(100,'-') << endl;
    cout << "Enter your name: ";
    string name;
    cin >> name;
    cout << "Enter your password: ";
    string password;
    cin >> password;
    cout << string(100,'=') << endl;
    return {name, password};
}

void displaySpecialMessage(string message) {
    cout << string(100,'-') << endl;
    cout << message << endl;
    cout << string(100,'-') << endl;
}
