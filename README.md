#  PROPERTY MANAGEMENT SYSTEM


# A Console-Based Property Management System

A terminal application built in C++ that connects **property owners** and **tenants** through a clean, menu-driven interface. Owners can post(list) properties for rent, tenants can browse and apply, and the whole process — from application to contract approval — is handled inside the program.

---

## What Can This System Do?

### For Property Owners
- Register an account and log back in anytime
- Add properties with details like type, location, area, and monthly rent
- **List**/**Post** properties for others to rent and make them visible to tenants, or **delist** them to hide them
- Edit or remove properties you own
- Review tenant applications and **approve** or ignore them
- View all your active rental contracts

### For Tenants
- Register an account and log back in anytime
- Browse all properties that owners have made available for rent
- Apply to a property by submitting a move-in date and duration
- Track all your applications (pending or approved)
- View your active lease details and simulate a rent payment
- Update your name and password anytime

---

## How to Compile and Run

```bash
g++ src/*.cpp -o bin/app
./bin/app
```

> Make sure you're in the root `property-management/` folder when running this.

---

## Project File Structure

```
property-management/
├── include/          # Header files — declarations of all classes and functions
│   ├── property.h    # Defines Property, Owner, Tenant, Contract, Date
│   ├── registry.h    # Defines the registry classes that store all data
│   ├── display.h     # Declares all screen/UI functions
│   └── session.h     # Declares all functions for what happens on all session
├── src/              # Source files — the actual logic
│   ├── main.cpp      # Starting point of the program
│   ├── property.cpp  # implementation for methods(functions) declared in property.h
│   ├── registry.cpp  # implementations for methods declared in registry.h
│   ├── display.cpp   # Outputs everything you see on the screen
│   └── session.cpp   # What happens when you pick a menu option(session)/implementation of functions declared in session.h
└── bin/              # Where the compiled program goes
```

---

## Understanding the Code — The Big Picture

The program is split into three clear responsibilities:

| File | Job |
|---|---|
| `display.cpp` | Draws everything on screen — boxes, menus, messages |
| `session.cpp` | Decides what happens when you make a choice |
| `registry.cpp` | Stores and retrieves all data — owners, tenants, properties, contracts |

---

## The Data Model — What Gets Stored

There are four main "things" (classes) the system keeps track of:

### Property
Represents a single rental unit an owner adds to the system.

| Field | What it means |
|---|---|
| `propertyID` | A unique number automatically assigned when the property is added |
| `ownerID` | Links this property to the owner who created it |
| `type` | e.g. Villa, Townhouse, Apartment |
| `location` | e.g. Addis Ababa, Bole |
| `description` | Any extra details the owner wants to add |
| `area` | Size in square meters |
| `rentalValue` | Monthly rent in ETB |
| `isListed` | Whether tenants can see and apply to this property |
| `isRented` | Whether the property is currently occupied |

---

### 👤 Owner
Represents a property owner registered in the system.

| Field | What it means |
|---|---|
| `ownerID` | Unique number assigned on registration |
| `name` | Owner's full name |
| `password` | Used to log back in |
| `propertyIDs` | A list of IDs pointing to all properties this owner has added |

> The owner doesn't store the full property — just the **ID**. The actual property lives in the `PropertyRegistry`, and the ID is used to look it up when needed.

---

### 🧑 Tenant
Represents someone looking to rent a property.

| Field | What it means |
|---|---|
| `tenantID` | Unique number assigned on registration |
| `name` | Tenant's full name |
| `password` | Used to log back in |

---

### 📄 Contract
Created when a tenant applies to a property. Starts as **pending** until the owner approves it.

| Field | What it means |
|---|---|
| `contractID` | Unique number assigned when the contract is created |
| `ownerID` | The owner of the property being rented |
| `tenantID` | The tenant who applied |
| `propertyID` | The property this contract is for |
| `date` | The tenant's requested move-in date (day, month, year) |
| `rentalAmount` | Monthly rent copied from the property at time of application |
| `contractDuration` | How many months the tenant wants to stay |
| `isActive` | `false` = pending approval, `true` = approved and active |

---

## Under the Hood — How the Registry Works

Think of the **Registry** as a filing cabinet. Every time you add an owner, tenant, property, or contract, it goes into the registry. The registry also hands out unique ID numbers automatically.

```
AppRegistry  ← one big container holding everything
├── OwnerRegistry      → stores all Owner objects
├── TenantRegistry     → stores all Tenant objects
├── PropertyRegistry   → stores all Property objects
└── ContractRegistry   → stores all Contract objects
```

There is **one** `AppRegistry` created in `main.cpp` and passed around to every part of the program. This means everyone shares the same data.

### How IDs are assigned

Every registry has a counter that starts at 0 and goes up by 1 each time something is added:

```cpp
// Inside PropertyRegistry::addProperty()
property.setPropertyID(++nextID);   // assigns ID 1, then 2, then 3...
properties.push_back(property);     // stores a copy in the list
return property.getPropertyID();    // returns the ID to the caller
```

The caller (in `session.cpp`) then stores that ID wherever it's needed:

```cpp
int id = registry.propertyRegistry.addProperty(newProperty);
owner.addProperty(id);   // owner remembers the ID, not the full property
```

Later, to get the property back:

```cpp
Property* prop = registry.propertyRegistry.getPropertyByID(id);
```

This returns a **pointer** — a direct reference to the real object inside the registry. If you change something through this pointer, it changes the actual stored data.

### How login works

Login doesn't use IDs — it searches by name and password:

```cpp
// Inside OwnerRegistry::verifyData()
for each owner in owners:
    if owner.name matches AND owner.password matches:
        return a pointer to that owner
return nullptr  // nothing found = login failed
```

---

## How the Flows Work — Step by Step

### Owner adds a property

1. Owner picks **My Properties → Add New Property**
2. A form appears asking for type, location, description, area, and rental value
3. A `Property` object is created and added to `PropertyRegistry` — it gets a unique ID
4. That ID is stored in the owner's `propertyIDs` list
5. The property is now saved but **not listed** — tenants can't see it yet

### Owner lists a property for rent

1. Owner picks **My Properties → List Properties**
2. Their properties are shown on screen
3. Owner enters the property's ID
4. `PropertyRegistry::listProperty(id)` sets `isListed = true` on that property
5. The property now appears when tenants browse

### Tenant applies to a property

1. Tenant picks **Browse New Properties**
2. The system loops through all properties and shows only those with `isListed = true`
3. Tenant enters the ID of the property they want
4. Tenant fills in a move-in date and duration
5. A `Contract` object is created with `isActive = false` (pending)
6. The contract is saved in `ContractRegistry`

### Owner approves an application

1. Owner picks **Applications Inbox**
2. The system finds all contracts where `ownerID` matches AND `isActive = false`
3. Owner enters the contract ID they want to approve
4. `ContractRegistry::activateContractByID(id)` sets `isActive = true`
5. The tenant's lease is now active

---

## How the Screen is Built (`display.cpp`)

All output uses **Unicode box-drawing characters** (like `┌ ─ ┐ │ └ ┘`) and **ANSI color codes** to produce the bordered interface you see in the terminal.

Everything you see on screen is built from a small set of internal drawing functions:

| Function | What it draws |
|---|---|
| `printBox(title, width)` | A titled header with a divider underneath |
| `printOpenBox(text, width, color)` | One row of text between two side borders |
| `printLine(width)` | The closing bottom border `└───┘` |
| `printKeyValue(key, value, width, color)` | A two-column row like `Property │ Villa at Bole` |
| `enterMessageBox(prompt, width)` | A prompt that reads a line of text from the user |

These raw functions are wrapped into friendlier names used everywhere else:

```cpp
displayHeader("MY PROPERTIES")        // → printBox(...)
displaySubHeader("Choose one:")        // → printOpenBox(..., INFO color)
displayValue("Some content")           // → printOpenBox(..., white)
displayKeyValue("Label", "Value")      // → printKeyValue(...)
displayEndLine()                       // → printLine(...)
displaySuccessMessage("Done!")         // → colored green text
displayErrorMessage("Failed!")         // → colored red text
```

### Color scheme

| Color | Used for |
|---|---|
| Yellow (gold) | Box borders |
| Bold gold | Titles and headings |
| White | Regular content |
| Bold green | Success messages |
| Bold red | Error messages |
| Bold cyan | Hints and sub-headings |
| Bold magenta | Key-value labels |
| Dimmed white | Secondary info |

---

## How the Sessions Work (`session.cpp`)

Every screen the user sees is controlled by a **session function**. Each one runs a loop that keeps showing a menu until the user picks "Back" or "Log Out".

```
main()
  └── initialPage()                          ← Main menu loop
        └── routeMainMenuChoice()
              ├── handleLogin()              ← Verifies credentials, launches session
              └── handleRegister()           ← Creates account, launches session
                    ├── handleOwnerSession()               ← Owner dashboard loop
                    │     └── handleMyPropertiesSession()  ← Property management loop
                    └── handleTenantSession()              ← Tenant dashboard loop
                          └── handleTenantLeaseSession()   ← Lease & payment loop
```

Two helper functions are used throughout session.cpp:

```cpp
// Checks if a number exists in a list — used to validate user input
bool checkValueExistence(int value, vector<int> list);

// Splits a string by a character — used to parse dates like "12/3/2025"
vector<string> splitString(string input, char separator);

// Lists all properties owned by an owner — used in 5 different places
void listOwnerProperties(Owner& owner, AppRegistry& registry);
```

---

## What's Not Done Yet

- **File persistence** — all data is lost when the program closes
- **Admin panel** — the option exists on the main menu but does nothing yet
- **Input validation** — typing letters where numbers are expected will crash the program
- **Reject application** — owners can approve but not explicitly reject (the tenant's application just stays pending)