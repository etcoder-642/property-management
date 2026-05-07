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

    // // Bottom
    // cout << "└";
    // for (int i = 0; i < width - 2; i++) cout << "─";
    // cout << "┘\n";
}

void printCell(const string &text, int colWidth, const char *color)
{
    string display = text;

    if (display.size() > (size_t)colWidth - 3)
        display = display.substr(0, colWidth - 6) + "...";
    int padding = colWidth - 3 - display.size(); // explicit space padding
    cout << color << " " << display;
    for (int i = 0; i < padding; i++)
        cout << " ";
    cout << " " << BORDER << "│";
}

void printSeveralInBox(vector<string> content, int width)
{
    int cols = content.size();
    int available = width - 1; // subtract opening │
    if (available % cols != 0)
        available += cols - (available % cols);
    int colWidth = available / cols;
    int actualWidth = available + 1; // add back the opening │

    cout << BORDER << "┌";
    for (int i = 0; i < actualWidth - 2; i++)
        cout << "─";
    cout << "┐\n";

    cout << BORDER << "│";
    for (string c : content)
        printCell(c, colWidth, TITLE);
    cout << "\n";

    cout << BORDER << "├";
    for (int i = 0; i < actualWidth - 2; i++)
        cout << "─";
    cout << "┤\n";
}

void printSeveralInOpenBox(vector<string> content, int width)
{
    int cols = content.size();
    int available = width - 1; // subtract opening │

    // bump width up until evenly divisible
    while (available % cols != 0)
        available++;
    int colWidth = available / cols;
    int actualWidth = available + 1; // add back the opening │

    cout << BORDER << "│";
    for (string c : content)
        printCell(c, colWidth, CONTENT);
    cout << "\n";
}

void printLine(int width)
{
    cout << BORDER << "└";
    for (int i = 0; i < width - 2; i++)
        cout << "─";
    cout << BORDER << "┘\n";
}

void printOpenBox(string content, int width)
{
    cout << BORDER << "│ " << CONTENT << content;
    for (int i = 0; i < width - 3 - content.size(); i++)
        cout << " ";
    cout << BORDER << "│\n";
}

void printSubBox(string content, int width)
{
    cout << BORDER << "│ " << INFO << content;
    for (int i = 0; i < width - 3 - content.size(); i++)
        cout << " ";
    cout << BORDER << "│\n";
}


void pause()
{
    cout << DIM << "\n Press Enter to continue... " << RESET;
    cin.ignore();
}

string enterMessageBox(string content, int width)
{
    string message;
    // Print prompt line (no closing │, user types here)
    cout << BORDER << "│ " << INPUT << content << " ";
    getline(cin, message);

    // Move cursor up 1 line, move to column `width`, draw closing │
    cout << "\033[1A"               // up 1 line
         << "\033[" << width << "G" // move to column = width
         << BORDER << "│\n";        // close the right wall

    // Print a clean divider after to maintain box illusion
    cout << BORDER << "├";
    for (int i = 0; i < width - 2; i++)
        cout << "─";
    cout << BORDER << "┤\n";

    return message;
}

string enterMessageBoxModified(string mainContent, string secondaryContent, int width)
{
    string message;
    // Print prompt line (no closing │, user types here)
    cout << BORDER << "│ " << INPUT << mainContent << DIM << secondaryContent << RESET << " ";
    getline(cin, message);

    // Move cursor up 1 line, move to column `width`, draw closing │
    cout << "\033[1A"               // up 1 line
         << "\033[" << width << "G" // move to column = width
         << BORDER << "│\n";        // close the right wall

    // Print a clean divider after to maintain box illusion
    cout << BORDER << "├";
    for (int i = 0; i < width - 2; i++)
        cout << "─";
    cout << BORDER << "┤\n";

    return message;
}

void displaySuccessMessage(string message)
{
    cout << SUCCESS << " " << message << RESET << endl;
}

void displayErrorMessage(string message)
{
    cout << ERROR << " " << message << RESET << endl;
}


void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int initialPage()
{
    clearScreen();
    string userChoice;
    printBox("PROPERTY MANAGEMENT SYSTEM", BOX_WIDTH);
    printOpenBox("[1] Log In", BOX_WIDTH);
    printOpenBox("[2] Register", BOX_WIDTH);
    printOpenBox("[3] Log In as Admin", BOX_WIDTH);
    printOpenBox("[4] About the System", BOX_WIDTH);
    printOpenBox("[5] Exit", BOX_WIDTH);
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
    printOpenBox("[1] Login as Owner", BOX_WIDTH);
    printOpenBox("[2] Login as a Tenant", BOX_WIDTH);
    printOpenBox("[3] Back", BOX_WIDTH);
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
    printOpenBox("[1] Register as Owner", BOX_WIDTH);
    printOpenBox("[2] Register as a Tenant", BOX_WIDTH);
    printOpenBox("[3] Back", BOX_WIDTH);
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
    string phoneNumber = enterMessageBox("Enter your phone number: ", BOX_WIDTH);
    return {name, password, phoneNumber};
}

int getOwnerSessionMenu(Owner &owner)
{
    string choice;
    clearScreen();
    printBox("WELCOME, " + owner.getName(), BOX_WIDTH);
    printOpenBox("[1] My Properties", BOX_WIDTH);
    printOpenBox("[2] Applications Inbox", BOX_WIDTH);
    printOpenBox("[3] View Contracts", BOX_WIDTH);
    printOpenBox("[4] Earnings Overview", BOX_WIDTH);
    printOpenBox("[5] Update Profile", BOX_WIDTH);
    printOpenBox("[6] Log Out", BOX_WIDTH);
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
    printOpenBox("[1] My Lease & Pay Rent", BOX_WIDTH);
    printOpenBox("[2] Browse New Properties", BOX_WIDTH);
    printOpenBox("[3] My Applications", BOX_WIDTH);
    printOpenBox("[4] Payment History", BOX_WIDTH);
    printOpenBox("[5] Update Profile", BOX_WIDTH);
    printOpenBox("[6] Log Out", BOX_WIDTH);
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
    printOpenBox("[1] View Properties", BOX_WIDTH);
    printOpenBox("[2] Add New Property", BOX_WIDTH);
    printOpenBox("[3] Remove Properties", BOX_WIDTH);
    printOpenBox("[4] Edit Property", BOX_WIDTH);
    printOpenBox("[5] List Properties", BOX_WIDTH);
    printOpenBox("[6] UnList Properties", BOX_WIDTH);
    printOpenBox("[7] Back", BOX_WIDTH);
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
    string dimensions = enterMessageBoxModified("Enter property dimensions", " (length & width, ex: 10 20): ", BOX_WIDTH);
    string rentalValueStr = enterMessageBoxModified("Enter rental value", " (per month value): ", BOX_WIDTH);
    return {type, location, description, dimensions, rentalValueStr};
}

void displayPropertyHeader(vector<string> propertyHeader)
{
    printSeveralInBox(propertyHeader, BOX_WIDTH);
}

void displayProperty(vector<string> propertyInfo)
{
    printSeveralInOpenBox(propertyInfo, BOX_WIDTH);
}

int displayPropertiesToBeRemoved(vector<vector<string>> propertiesInfo)
{
    clearScreen();
    printBox("REMOVE PROPERTY", BOX_WIDTH);
    printSubBox("Choose the one you want to remove:", BOX_WIDTH);
    for(int i = 0; i < propertiesInfo.size(); i++)
    {
       string p = "[" + to_string(i) + "] " + "A " + propertiesInfo[i][1] + " Located at " + propertiesInfo[i][0];
       printOpenBox(p, BOX_WIDTH);
    }
    printLine(BOX_WIDTH);
    cout << BORDER << "  [>] " << INPUT;
    string choice = "";
    getline(cin, choice);
    int res = stoi(choice);
    return stoi(propertiesInfo[res][5]);
}
