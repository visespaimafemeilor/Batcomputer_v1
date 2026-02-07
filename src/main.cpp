#include <iostream>
#include <string>
#include <limits>
#include "manager/database_manager.h"
#include "manager/combat_simulator.h"
#include "manager/operations_coordinator.h"
#include "manager/entity_factory.h"
#include "exceptions.h"
#include "criminals/criminals.h"
#include "family.h"
#include "batsuit.h"

void handleDatabaseMenu(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const CombatSimulator& simulator);
void handleOperationsMenu(const CombatSimulator& simulator, const OperationsCoordinator& ops, const std::vector<std::shared_ptr<DatabaseEntry>>& database);
void handleBatCaveMenu(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const OperationsCoordinator& ops);
void handleAdminMenu(const EntityFactory& factory, const std::vector<std::shared_ptr<DatabaseEntry>>& database);


int main(const int argc, char** argv) {

    // Central shared database and managers
    std::vector<std::shared_ptr<DatabaseEntry>> database;
    const std::string dbFilename = "database.txt";

    const DatabaseManager dbManager(database, dbFilename);
    const EntityFactory factory(database);
    const CombatSimulator simulator(database);
    const OperationsCoordinator ops(database);

    // Non-interactive command mode: add a criminal and exit
    if (argc > 1) {
        if (const std::string cmd = argv[1]; cmd == "add-criminal") {
            try {
                dbManager.load();
            } catch (const BatcomputerException& e) {
                std::cerr << "Initialization error: " << e.what() << "\n";
            }

            // Perform interactive add (reads from stdin)
            factory.addNewCriminal();

            try {
                dbManager.save();
                std::cout << "[OK] Criminal added and database saved.\n";
            } catch (const std::exception& e) {
                std::cerr << "Save failed: " << e.what() << "\n";
                return 2;
            }
            return 0;
        }
        // unknown command -> fallthrough to interactive mode
    }

    try {
        std::cout << "Welcome, Dark Knight. Initializing Bat-Computer managers...\n";
        dbManager.load();
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
        std::cout << "5) Quick Add Criminal\n";
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
            case 1: handleDatabaseMenu(database, simulator); break;
            case 2: handleOperationsMenu(simulator, ops, database); break;
            case 3: handleBatCaveMenu(database, ops); break;
            case 4: handleAdminMenu(factory, database); break;
            case 5: factory.addNewCriminal(); break;
            case 0:
                try {
                    dbManager.save();
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

void handleDatabaseMenu(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const CombatSimulator& simulator) {
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
            case 1: Criminal::showAll(database); break;
            case 2: Family::showAll(database); break;
            case 3:
                std::cout << "Enter name: "; std::getline(std::cin, buffer);
                Criminal::searchByName(database, buffer);
                break;
            case 4:
                std::cout << "Enter name: "; std::getline(std::cin, buffer);
                simulator.showCriminalIntel(buffer);
                break;
            case 5: {
                std::cout << "\n=== POLYMORPHIC OVERVIEW ===\n";
                for (const auto& e : database) {
                    std::cout << "[" << e->type() << "] " << e->summary() << " | Threat: " << e->assessThreat() << "\n";
                }
                break;
            }
            case 0:
                std::cout << "Returning to previous menu...\n";
                break;
            default:
                std::cout << "[ERROR] Invalid selection: '" << choice << "'. Please try again.\n";
                break;
        }
    }
}

void handleOperationsMenu(const CombatSimulator& simulator, const OperationsCoordinator& ops, const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- [OPERATIONS & TACTICS] ---\n";
        std::cout << "1) 1vs1 Battle Simulation\n";
        std::cout << "2) Arkham Blackout (Mass Escape Simulation)\n";
        std::cout << "3) Generate Strategic Crime Report\n";
        std::cout << "4) Simulate Escape Attempt (Single)\n";
        std::cout << "5) Interactive Entry Hook (Polymorphic Interaction)\n";
        std::cout << "6) Simulate Gotham Siege\n";
        std::cout << "7) Run Forensics Analysis\n";
        std::cout << "8) Cyber Defense (Scan for Hackers)\n";
        std::cout << "9) Underworld Surveillance (Scan for Crime Lords)\n";
        std::cout << "10) Global Tactical Simulation\n";
        std::cout << "11) Compare Efficency\n";
        std::cout << "0) BACK TO MAIN MENU\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch (choice) {
            case 1: {
                std::string fam, crim;
                std::cout << "Family Member: "; std::getline(std::cin, fam);
                std::cout << "Criminal: "; std::getline(std::cin, crim);
                simulator.simulateBattle(fam, crim); break;
            }
            case 2: {
                double sec; std::cout << "Security Level (1-100): "; std::cin >> sec;
                ops.simulateArkhamBlackout(sec); break;
            }
            case 3: ops.generateCrimeReport(); break;
            case 4: {
                std::string n; std::cout << "Criminal Name: "; std::getline(std::cin, n);
                double s; std::cout << "Facility Security (1-10): "; std::cin >> s;
                simulator.simulateEscape(n, s); break;
            }
            case 5: {
                int i1, i2;
                std::cout << "\n=== POLYMORPHIC OVERVIEW ===\n";
                for (const auto& e : database) {
                    std::cout << "[" << e->type() << "] " << e->summary() << " | Threat: " << e->assessThreat() << "\n";
                }
                std::cout << "Index 1: "; std::cin >> i1;
                std::cout << "Index 2: "; std::cin >> i2;
                simulator.performInteraction(i1, i2); break;
            }
            case 6: {
                ops.runSiege(); break;
            }
            case 7: {
                ops.runForensics(); break;
            }
            case 8:
                ops.runGlobalCyberDefense();
                break;
            case 9:
                ops.runUnderworldSting();
                break;
            case 10:
                ops.runGlobalTacticalSimulation();
                break;
            case 11: {
                int i1, i2;
                std::cout << "\nIntroduceti indecsii celor doua entitati de comparat:\n";
                std::cout << "Index 1: "; std::cin >> i1;
                std::cout << "Index 2: "; std::cin >> i2;

                try {
                    simulator.analyzeMatchup(i1, i2);
                } catch (const DatabaseOperationException& e) {
                    std::cerr << "\n[CRITICAL ERROR] " << e.what() << "\n";
                    std::cout << "Sfat: Verificati daca indecsii introdusi exista in lista de mai sus.\n";
                }
                break;
            }
            case 0:
                std::cout << "Returning to previous menu...\n";
                break;
            default:
                std::cout << "[ERROR] Invalid selection: '" << choice << "'. Please try again.\n";
                break;
        }
    }
}

void handleBatCaveMenu(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const OperationsCoordinator& ops) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- [BAT-CAVE SYSTEMS] ---\n";
        std::cout << "1) Show Batsuit Status\n";
        std::cout << "2) Run Maintenance\n";
        std::cout << "3) Redistribute Suit Integrity\n";
        std::cout << "4) Combat Survival Simulation\n";
        std::cout << "0) BACK TO MAIN MENU\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch (choice) {
            case 1: Batsuit::showAll(database); break;
            case 2: ops.batcaveMaintenance(); break;
            case 3: ops.runSuitRebalance(); break;
            case 4: {
                std::string name;
                std::cout << "Target enemy for simulation: ";
                std::getline(std::cin, name);
                ops.checkSurvival(name);
                break;

            }
            case 0:
                std::cout << "Returning to previous menu...\n";
                break;
            default:
                std::cout << "[ERROR] Invalid selection: '" << choice << "'. Please try again.\n";
                break;

        }
    }
}

void handleAdminMenu(const EntityFactory& factory, const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
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
            case 1: factory.addNewCriminal(); break;
            case 2: factory.addNewFamilyMember(); break;
            case 3: factory.addNewBatsuitPart(); break;
            case 4: {
                    std::string n; std::cout << "Name: "; std::getline(std::cin, n);
                    Criminal::promoteByName(database, n);
                    break;
            }
            case 0:
                std::cout << "Returning to previous menu...\n";
                break;
            default:
                std::cout << "[ERROR] Invalid selection: '" << choice << "'. Please try again.\n";
                break;
        }
    }
}
