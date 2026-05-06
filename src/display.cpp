#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "../include/property.h"
#include "../include/registry.h"
#include "../include/display.h"

#define BORDER  "\033[33m"   // yellow/gold
#define TITLE   "\033[1;33m" // bold gold
#define CONTENT "\033[37m"   // white

// Semantic
#define SUCCESS "\033[1;32m" // bold green
#define ERROR   "\033[1;31m" // bold red
#define WARNING "\033[1;33m" // bold yellow — use sparingly, close to BORDER
#define INFO    "\033[1;36m" // bold cyan — for status labels, hints
#define DIM     "\033[2;37m" // dimmed white — for secondary text, timestamps
#define INPUT   "\033[1;37m" // bold white — what the user types
#define RESET   "\033[0m"

using namespace std;

void printBox(string title, int width) {
    // Top border
    cout << BORDER << "┌";
    for (int i = 0; i < width - 2; i++) cout << "─";
    cout << BORDER << "┐\n";

    // Title line (centered)
    int padding = (width - 2 - title.size()) / 2;
    cout << BORDER << "│";
    for (int i = 0; i < padding; i++) cout << " ";
    cout << TITLE << title;
    for (int i = 0; i < width - 2 - padding - title.size(); i++) cout << " ";
    cout << BORDER << "│\n";

    // Divider
    cout << BORDER << "├";
    for (int i = 0; i < width - 2; i++) cout << "─";
    cout << BORDER << "┤\n";

    // // Bottom
    // cout << "└";
    // for (int i = 0; i < width - 2; i++) cout << "─";
    // cout << "┘\n";
}

void printLine(int width) {
    cout << BORDER << "└";
    for (int i = 0; i < width - 2; i++) cout << "─";
    cout << BORDER << "┘\n";
}

void printOpenBox(string content, int width)
{
    cout << BORDER << "│ " << CONTENT << content;
    for (int i = 0; i < width - 3 - content.size(); i++) cout << " ";
    cout << BORDER << "│\n";
}

void pause()
{
    cout << DIM << "\n Press Enter to continue..." << RESET;
    cin.ignore();
}


string enterMessageBox(string content, int width) {
    string message;
    // Print prompt line (no closing │, user types here)
    cout << BORDER << "│ " << INPUT << content << " ";
    getline(cin, message);

      // Move cursor up 1 line, move to column `width`, draw closing │
    cout << "\033[1A"          // up 1 line
         << "\033[" << width << "G"  // move to column = width
         << BORDER << "│\n";  // close the right wall
    
    // Print a clean divider after to maintain box illusion
    cout << BORDER << "├";
    for (int i = 0; i < width - 2; i++) cout << "─";
    cout << BORDER << "┤\n";
    
    return message;
}

void displaySuccessMessage(string message) 
{
    cout << SUCCESS << " " << message << RESET << endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int initialPage() {
    clearScreen();
    string userChoice;
    printBox("PROPERTY MANAGEMENT SYSTEM", 50);
    printOpenBox("[1] Log In", 50);
    printOpenBox("[2] Register", 50);
    printOpenBox("[3] Log In as Admin", 50);
    printOpenBox("[4] About the System", 50);
    printOpenBox("[5] Exit", 50);
    printLine(50);
    getline(cin, userChoice);
    int res = stoi(userChoice);
    return res;
}

int handleLoginUI()
{
    clearScreen();
    string choice;
    printBox("LOGIN", 50);
    printOpenBox("[1] Login as Owner", 50);
    printOpenBox("[2] Login as a Tenant", 50);
    printOpenBox("[3] Back", 50);
    printLine(50);
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

int handleRegisterUI()
{
    clearScreen();
    string choice;
    printBox("REGISTER", 50);
    printOpenBox("[1] Register as Owner", 50);
    printOpenBox("[2] Register as a Tenant", 50);
    printOpenBox("[3] Back", 50);
    printLine(50);
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

vector<string> handleOwnerRegistry() {
    clearScreen();
    printBox("OWNER REGISTRATION", 50);
    string name = enterMessageBox("Enter your name: ", 50);
    string password = enterMessageBox("Enter your password: ", 50);
    string phoneNumber = enterMessageBox("Enter your phone number: ", 50);
    return {name, password, phoneNumber};
}

int getOwnerSessionMenu(Owner &owner)
{
    string choice;
    clearScreen();
    printBox("WELCOME, " + owner.getName(), 50);
    printOpenBox("[1] View Properties", 50);
    printOpenBox("[2] Add Property", 50);
    printOpenBox("[3] Remove Property", 50);
    printOpenBox("[4] View Tenants", 50);
    printOpenBox("[5] Log Out", 50);
    printLine(50);
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

