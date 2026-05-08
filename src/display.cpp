#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "../include/property.h"
#include "../include/registry.h"
#include "../include/display.h"

#define BORDER "\033[33m"  // yellow/gold
#define TITLE "\033[1;33m" // bold gold
#define CONTENT "\033[37m" // white

// Semantic
#define SUCCESS "\033[1;32m" // bold green
#define ERROR "\033[1;31m"   // bold red
#define WARNING "\033[1;33m" // bold yellow — use sparingly, close to BORDER
#define INFO "\033[1;36m"    // bold cyan — for status labels, hints
#define DIM "\033[2;37m"     // dimmed white — for secondary text, timestamps
#define INPUT "\033[1;37m"   // bold white — what the user types
#define RESET "\033[0m"

#define BOX_WIDTH 100

using namespace std;

// prints a given string in a box used for titles with a given width

void printBox(string title, int width)
{
    // Top border
    cout << BORDER << "┌";
    for (int i = 0; i < width - 2; i++)
        cout << "─";
    cout << BORDER << "┐\n";

    // Title line (centered)
    int padding = (width - 2 - title.size()) / 2;
    cout << BORDER << "│";
    for (int i = 0; i < padding; i++)
        cout << " ";
    cout << TITLE << title;
    for (int i = 0; i < width - 2 - padding - title.size(); i++)
        cout << " ";
    cout << BORDER << "│\n";

    // Divider
    cout << BORDER << "├";
    for (int i = 0; i < width - 2; i++)
        cout << "─";
    cout << BORDER << "┤\n";
}

// prints a straight line with given width

void printLine(int width)
{
    cout << BORDER << "└";
    for (int i = 0; i < width - 2; i++)
        cout << "─";
    cout << BORDER << "┘\n";
}

// prints a string inside an openBox with given width and a given color
// And open Box is a box with no upper and lower borders just the side borders

void printOpenBox(string content, int width, string color)
{
    cout << BORDER << "│ " << color << content;
    for (int i = 0; i < width - 3 - content.size(); i++)
        cout << " ";
    cout << BORDER << "│\n";
}

// pauses code execution

void pause()
{
    cout << DIM << "\n Press Enter to continue... " << RESET;
    cin.ignore();
}

// a function to collect a message from the user using getLine. 

string enterMessageBox(string content, int width)
{
    string message;
    // Print prompt line (no closing │, user types here)
    cout << BORDER << "│ " << INPUT << content << " ";
    getline(cin, message);
    return message;
}

// a function to collect a message from the user using getLine. 

string enterMessageBoxModified(string mainContent, string secondaryContent, int width)
{
    string message;
    // Print prompt line (no closing │, user types here)
    cout << BORDER << "│ " << INPUT << mainContent << DIM << secondaryContent << RESET << " ";
    getline(cin, message);
    return message;
}

// displays a string message using a success color

void displaySuccessMessage(string message)
{
    cout << SUCCESS << " " << message << RESET << endl;
}

// displays an error message with a red color

void displayErrorMessage(string message)
{
    cout << ERROR << " " << message << RESET << endl;
}

// clearn the entire screen for the next session

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// the initial page users will see when entering the program

int initialPage()
{
    clearScreen();
    string userChoice;
    printBox("PROPERTY MANAGEMENT SYSTEM", BOX_WIDTH);
    printOpenBox("[1] Log In", BOX_WIDTH, CONTENT);
    printOpenBox("[2] Register", BOX_WIDTH, CONTENT);
    printOpenBox("[3] Log In as Admin", BOX_WIDTH, CONTENT);
    printOpenBox("[4] Exit", BOX_WIDTH, CONTENT);
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    getline(cin, userChoice);
    int res = stoi(userChoice);
    return res;
}

int handleLoginUI()
{
    clearScreen();
    string choice;
    printBox("LOGIN", BOX_WIDTH);
    printOpenBox("[1] Login as Owner", BOX_WIDTH, CONTENT);
    printOpenBox("[2] Login as a Tenant", BOX_WIDTH, CONTENT);
    printOpenBox("[3] Back", BOX_WIDTH, CONTENT);
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

int handleRegisterUI()
{
    clearScreen();
    string choice;
    printBox("REGISTER", BOX_WIDTH);
    printOpenBox("[1] Register as Owner", BOX_WIDTH, CONTENT);
    printOpenBox("[2] Register as a Tenant", BOX_WIDTH, CONTENT);
    printOpenBox("[3] Back", BOX_WIDTH, CONTENT);
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

vector<string> displayRegistry(int registerChoice)
{
    string role = (registerChoice == 1) ? "OWNER" : "TENANT";
    clearScreen();
    printBox(role + " REGISTRATION", BOX_WIDTH);
    string name = enterMessageBox("Enter your name: ", BOX_WIDTH);
    string password = enterMessageBox("Enter your password: ", BOX_WIDTH);
    return {name, password};
}

int getOwnerSessionMenu(Owner &owner)
{
    string choice;
    clearScreen();
    printBox("WELCOME, " + owner.getName(), BOX_WIDTH);
    printOpenBox("[1] My Properties", BOX_WIDTH, CONTENT);
    printOpenBox("[2] Applications Inbox", BOX_WIDTH, CONTENT);
    printOpenBox("[3] View Contracts", BOX_WIDTH, CONTENT);
    printOpenBox("[4] Update Profile", BOX_WIDTH, CONTENT);
    printOpenBox("[5] Log Out", BOX_WIDTH, CONTENT);
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

int getTenantSessionMenu(Tenant &tenant)
{
    string choice;
    clearScreen();
    printBox("WELCOME, " + tenant.getName(), BOX_WIDTH);
    printOpenBox("[1] My Lease & Pay Rent", BOX_WIDTH, CONTENT);
    printOpenBox("[2] Browse New Properties", BOX_WIDTH, CONTENT);
    printOpenBox("[3] My Applications", BOX_WIDTH, CONTENT);
    printOpenBox("[4] Update Profile", BOX_WIDTH, CONTENT);
    printOpenBox("[5] Log Out", BOX_WIDTH, CONTENT);
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

int getMyPropertiesSession()
{
    string choice;
    clearScreen();
    printBox("MY PROPERTIES", BOX_WIDTH);
    printOpenBox("[1] View Properties", BOX_WIDTH, CONTENT);
    printOpenBox("[2] Add New Property", BOX_WIDTH, CONTENT);
    printOpenBox("[3] Remove Properties", BOX_WIDTH, CONTENT);
    printOpenBox("[4] Edit Property", BOX_WIDTH, CONTENT);
    printOpenBox("[5] List Properties", BOX_WIDTH, CONTENT);
    printOpenBox("[6] Delist Properties", BOX_WIDTH, CONTENT);
    printOpenBox("[7] Back", BOX_WIDTH, CONTENT);
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

int getTenantLeaseSession()
{
    string choice;
    clearScreen();
    printBox("MY PROPERTIES", BOX_WIDTH);
    printOpenBox("[1] View Current Lease", BOX_WIDTH, CONTENT);
    printOpenBox("[2] Pay Rent", BOX_WIDTH, CONTENT);
    printOpenBox("[3] Back", BOX_WIDTH, CONTENT);
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    getline(cin, choice);
    int res = stoi(choice);
    return res;
}

vector<string> newPropertyForm()
{
    clearScreen();
    printBox("ADD NEW PROPERTY", BOX_WIDTH);
    string type = enterMessageBoxModified("Enter property type", " (e.g., Villa, Townhouse): ", BOX_WIDTH);
    string location = enterMessageBox("Enter property location: ", BOX_WIDTH);
    string description = enterMessageBox("Enter property description: ", BOX_WIDTH);
    string area = enterMessageBoxModified("Enter property area", " (NUMBER ONLY, ex: 10): ", BOX_WIDTH);
    string rentalValueStr = enterMessageBoxModified("Enter rental value", " (per month value): ", BOX_WIDTH);
    return {type, location, description, area, rentalValueStr};
}

vector<string> propertyApplicationForm()
{
    clearScreen();
    printBox("ADD NEW PROPERTY", BOX_WIDTH);
    string moveInDate = enterMessageBoxModified("Enter move-in date", " (NUMBER ONLY(D/M/Y)e.g. 12/3/4): ", BOX_WIDTH);
    string duration = enterMessageBox("Enter contract duration: ", BOX_WIDTH);
    return {moveInDate, duration};
}

void displayHeader(string str)
{
    printBox(str, BOX_WIDTH);
}

void displaySubHeader(string str)
{
    printOpenBox(str, BOX_WIDTH, INFO);
}

void displayProperty(int num, vector<string> propertyInfo)
{
    cout << CONTENT << "[" << num << "] ";
    string str = "A " + propertyInfo[1] + " Located At " + propertyInfo[0] + " with an area of " + propertyInfo[4] + " valued at " + propertyInfo[3];
    cout << str << RESET << endl;
}

int receiveData()
{
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    string choice = "";
    getline(cin, choice);
    int res = stoi(choice);
    return stoi(choice);
}