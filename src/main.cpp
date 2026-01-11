#include <iostream>
#include <string>
#include <limits>
#include "batcomputer.h"
#include "exceptions.h"

// --- PROTOTIPURI SUB-MENIURI ---
void handleDatabaseMenu(BatComputer& bc);
void handleOperationsMenu(BatComputer& bc);
void handleBatCaveMenu(BatComputer& bc);
void handleAdminMenu(BatComputer& bc);

// --- FUNCTII UTILS ---
void clearScreen() {
    std::cout << std::string(5, '\n');
}

int main() {
    BatComputer bc;

    try {
        std::cout << "Welcome, Dark Knight. Initializing Bat-Computer...\n";
        bc.loadDatabase();
    } catch (const BatcomputerException& e) {
        std::cerr << "Initialization error: " << e.what() << "\n";
    }

    int mainChoice = -1;
    while (mainChoice != 0) {
        std::cout << "\n====================================\n";
        std::cout << "      BAT-COMPUTER: MAIN TERMINAL   \n";
        std::cout << "====================================\n";
        std::cout << "1) [DATABASE]   - View, Search & Intel\n";
        std::cout << "2) [OPERATIONS] - Battles & Simulations\n";
        std::cout << "3) [BAT-CAVE]   - Maintenance & Suits\n";
        std::cout << "4) [ADMIN]      - Add New Records\n";
        std::cout << "0) [EXIT]       - Save & Shut Down\n";
        std::cout << "------------------------------------\n";
        std::cout << "Selection: ";

        if (!(std::cin >> mainChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (mainChoice) {
            case 1: handleDatabaseMenu(bc); break;
            case 2: handleOperationsMenu(bc); break;
            case 3: handleBatCaveMenu(bc); break;
            case 4: handleAdminMenu(bc); break;
            case 0:
                try {
                    bc.saveDatabase();
                } catch (const std::exception& e) {
                    std::cerr << "Save failed: " << e.what() << "\n";
                }
                std::cout << "Stay vigilant. Gotham still needs you.\n";
                break;
            default:
                std::cout << "Invalid access code.\n";
        }
    }
    return 0;
}

// ==========================================
//          IMPLEMENTARE SUB-MENIURI
// ==========================================

void handleDatabaseMenu(BatComputer& bc) {
    int choice = -1;
    std::string buffer;
    while (choice != 0) {
        std::cout << "\n--- [DATABASE TERMINAL] ---\n";
        std::cout << "1) Show All Criminals\n";
        std::cout << "2) Show Bat-Family Members\n";
        std::cout << "3) Search Criminal by Name\n";
        std::cout << "4) Show Criminal Intel\n";
        std::cout << "5) Polymorphic Overview (All Entries)\n";
        std::cout << "0) BACK TO MAIN MENU\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch (choice) {
            case 1: bc.showAllCriminals(); break;
            case 2: bc.showBatFamily(); break;
            case 3:
                std::cout << "Enter name: "; std::getline(std::cin, buffer);
                bc.searchCriminal(buffer); break;
            case 4:
                std::cout << "Enter name: "; std::getline(std::cin, buffer);
                bc.showCriminalIntel(buffer); break;
            case 5: bc.showPolymorphicDatabase(); break;
        }
    }
}

void handleOperationsMenu(BatComputer& bc) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- [OPERATIONS & TACTICS] ---\n";
        std::cout << "1) 1vs1 Battle Simulation\n";
        std::cout << "2) Arkham Blackout (Mass Escape Simulation)\n";
        std::cout << "3) Generate Strategic Crime Report\n";
        std::cout << "4) Simulate Escape Attempt (Single)\n";
        std::cout << "5) Interactive Entry Hook (Polymorphic Interaction)\n";
        std::cout << "0) BACK TO MAIN MENU\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch (choice) {
            case 1: {
                std::string fam, crim;
                std::cout << "Family Member: "; std::getline(std::cin, fam);
                std::cout << "Criminal: "; std::getline(std::cin, crim);
                bc.simulateBattle(fam, crim); break;
            }
            case 2: {
                double sec; std::cout << "Security Level (1-100): "; std::cin >> sec;
                bc.simulateArkhamBlackout(sec); break;
            }
            case 3: bc.generateCrimeReport(); break;
            case 4: {
                std::string n; std::cout << "Criminal Name: "; std::getline(std::cin, n);
                double s; std::cout << "Facility Security (1-10): "; std::cin >> s;
                bc.simulateEscape(n, s); break;
            }
            case 5: {
                int i1, i2;
                bc.showPolymorphicDatabase();
                std::cout << "Index 1: "; std::cin >> i1;
                std::cout << "Index 2: "; std::cin >> i2;
                bc.performInteraction(i1, i2); break;
            }
        }
    }
}

void handleBatCaveMenu(BatComputer& bc) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- [BAT-CAVE SYSTEMS] ---\n";
        std::cout << "1) Show Batsuit Status\n";
        std::cout << "2) Run Maintenance\n";
        std::cout << "0) BACK TO MAIN MENU\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch (choice) {
            case 1: bc.showBatsuit(); break;
            case 2: bc.batcaveMaintenance(); break;
        }
    }
}

void handleAdminMenu(BatComputer& bc) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- [ADMINISTRATIVE ACCESS] ---\n";
        std::cout << "1) Add New Criminal\n";
        std::cout << "2) Add New Family Member\n";
        std::cout << "3) Add New Batsuit Part\n";
        std::cout << "4) Promote Existing Criminal\n";
        std::cout << "0) BACK TO MAIN MENU\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch (choice) {
            case 1: bc.addNewCriminal(); break;
            case 2: bc.addNewFamilyMember(); break;
            case 3: bc.addNewBatsuitPart(); break;
            case 4: {
                std::string n; std::cout << "Name: "; std::getline(std::cin, n);
                bc.promoteCriminal(n); break;
            }
        }
    }
}