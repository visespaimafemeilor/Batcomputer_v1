#include <iostream>
#include <string>
#include <limits>
#include "batcomputer.h"
#include "exceptions.h"

void displayMenu() {
    std::cout << "\n==========================\n";
    std::cout << "        BAT-COMPUTER      \n";
    std::cout << "==========================\n";
    std::cout << "1) Show Criminal Database\n";
    std::cout << "2) Show Bat-Family Members\n";
    std::cout << "3) Show Batsuit Loadout\n";
    std::cout << "4) Show Criminal Intel\n";
    std::cout << "5) Search Criminal by Name\n";
    std::cout << "7) Simulate Battle (Family vs Criminal)\n";
    std::cout << "9) Promote Criminal & Show Threat\n";
    std::cout << "10) Simulate Escape Attempt\n";
    std::cout << "11) Show Database Polymorphically\n";
    std::cout << "14) Interact Two Entries (Indices)\n";
    std::cout << "15) Add New Criminal\n";
    std::cout << "16) Add New Family Member\n";
    std::cout << "17) Add New Batsuit Component\n";
    std::cout << "0) Exit & Save\n";
    std::cout << "--------------------------\n";
    std::cout << "Enter choice: ";
}

int main() {
    BatComputer bc;

    try {
        std::cout << "Welcome, Dark Knight. Initializing systems...\n";
        bc.loadDatabase();
    } catch (const BatcomputerException& e) {
        std::cerr << "Initialization warning: " << e.what() << "\n";
        std::cout << "Starting with a clean database.\n";
    }

    int choice = -1;
    std::string inputBuffer;

    while (choice != 0) {
        displayMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: bc.showAllCriminals(); break;
                case 2: bc.showBatFamily(); break;
                case 3: bc.showBatsuit(); break;

                case 4: {
                    std::cout << "Enter criminal name: ";
                    std::getline(std::cin, inputBuffer);
                    bc.showCriminalIntel(inputBuffer);
                    break;
                }

                case 5: {
                    std::cout << "Search name: ";
                    std::getline(std::cin, inputBuffer);
                    bc.searchCriminal(inputBuffer);
                    break;
                }

                case 7: {
                    std::string famName, crimName;
                    std::cout << "Family Member Codename: "; std::getline(std::cin, famName);
                    std::cout << "Criminal Name: "; std::getline(std::cin, crimName);
                    bc.simulateBattle(famName, crimName);
                    break;
                }

                case 9: {
                    std::cout << "Promote criminal name: ";
                    std::getline(std::cin, inputBuffer);
                    bc.promoteCriminal(inputBuffer);
                    break;
                }

                case 10: {
                    std::cout << "Criminal name: "; std::getline(std::cin, inputBuffer);
                    double sec;
                    std::cout << "Security Level (1-10): "; std::cin >> sec;
                    bc.simulateEscape(inputBuffer, sec);
                    break;
                }

                case 11: bc.showPolymorphicDatabase(); break;

                case 14: {
                    int i1, i2;
                    bc.showPolymorphicDatabase(); // Arătăm indicii
                    std::cout << "Select first index: "; std::cin >> i1;
                    std::cout << "Select second index: "; std::cin >> i2;
                    bc.performInteraction(i1, i2);
                    break;
                }

                case 15: bc.addNewCriminal(); break;
                case 16: bc.addNewFamilyMember(); break;
                case 17: bc.addNewBatsuitPart(); break;

                case 0:
                    bc.saveDatabase();
                    std::cout << "Exiting Bat-Computer... Stay vigilant, Batman.\n";
                    break;

                default:
                    std::cout << "Unknown command. Access denied.\n";
            }
        } catch (const BatcomputerException& e) {
            std::cerr << "\n[DATABASE ERROR] " << e.what() << "\n";
        }
    }

    return 0;
}