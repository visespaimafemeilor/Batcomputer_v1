#include "batcomputer.h"
#include "criminals/criminals.h"
#include "family.h"
#include "batsuit.h"
#include "exceptions.h"
#include "criminals/hacker.h"
#include "criminals/bank_robber.h"
#include "criminals/metahuman.h"
#include "criminals/crimeLord.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// --- GESTIUNE DATABASE ---

void BatComputer::loadDatabase() {
    std::ifstream fin(dbFilename);
    if (!fin) {
        throw FileLoadException(dbFilename);
    }

    int total;
    if (!(fin >> total)) return;

    database.clear();
    for (int i = 0; i < total; ++i) {
        auto obj = DatabaseEntry::createFromStream(fin);
        if (obj) {
            database.push_back(obj);
        }
    }
    std::cout << "[SYSTEM] Loaded " << database.size() << " entities.\n";
}

void BatComputer::saveDatabase() {
    std::ofstream fout(dbFilename);
    if (!fout) {
        throw DatabaseOperationException("Could not open file for saving.");
    }

    fout << database.size() << "\n";
    for (const auto& entry : database) {
        entry->save(fout);
    }
    std::cout << "[SYSTEM] Progress saved to " << dbFilename << ".\n";
}

void BatComputer::showAllCriminals() const {
    Criminal::showAll(this->database);
}

void BatComputer::showBatFamily() const {
    Family::showAll(this->database);
}

void BatComputer::showBatsuit() const {
    Batsuit::showAll(this->database);
}

void BatComputer::searchCriminal(const std::string& name) const {
    Criminal::searchByName(this->database, name);
}

void BatComputer::promoteCriminal(const std::string& name) {
    Criminal::promoteByName(this->database, name);
}

void BatComputer::simulateBattle(const std::string& familyMember, const std::string& criminalName) {
    std::shared_ptr<Family> vigilante = nullptr;
    std::shared_ptr<Criminal> enemy = nullptr;

    // Căutăm ambele entități în database
    for (auto& e : database) {
        if (auto f = std::dynamic_pointer_cast<Family>(e)) {
            if (f->getCodename() == familyMember) vigilante = f;
        }
        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
            if (c->getName() == criminalName) enemy = c;
        }
    }

    if (vigilante && enemy) {
        std::cout << "\n--- BATTLE SIMULATION ---\n";
        std::cout << vigilante->fightReport(*enemy);
        std::cout << vigilante->simulateBattle(*enemy);
    } else {
        std::cout << "Simulation failed: Target(s) not found.\n";
    }
}

void BatComputer::performInteraction(int idx1, int idx2) {
    if (idx1 >= 0 && (size_t)idx1 < database.size() && idx2 >= 0 && (size_t)idx2 < database.size()) {
        std::cout << "Result: " << database[idx1]->interact(*database[idx2]) << "\n";
    } else {
        std::cout << "Invalid indices for interaction.\n";
    }
}

void BatComputer::showPolymorphicDatabase() const {
    std::cout << "\n=== POLYMORPHIC OVERVIEW ===\n";
    for (const auto& e : database) {
        std::cout << "[" << e->type() << "] " << e->summary() << " | Threat: " << e->assessThreat() << "\n";
    }
}

void BatComputer::simulateEscape(const std::string& name, double securityLevel) const {
    for (const auto& e : database) {
        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
            if (c->getName() == name) {
                bool escaped = c->simulateEscape(securityLevel);
                std::cout << (escaped ? "ESCAPED!" : "Contained.") << "\n";
                return;
            }
        }
    }
    std::cout << "Criminal not found.\n";
}

void BatComputer::showCriminalIntel(const std::string& name) const {
    for (const auto& e : database) {
        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
            if (c->getName() == name) {
                const auto& intel = c->getIntel();
                std::cout << "\nIntel report for " << c->getName() << ":\n";
                if (intel.empty()) std::cout << "No intel available.\n";
                else {
                    for (const auto& i : intel) std::cout << "--> " << i << "\n";
                }
                return;
            }
        }
    }
    std::cout << "Criminal not found.\n";
}

void BatComputer::addNewCriminal() {
    std::string name;
    int id, rank, typeChoice;

    std::cout << "\n--- ADD NEW CRIMINAL ---\n";
    std::cout << "Select Type: 1) Generic 2) Hacker 3) Bank Robber 4) MetaHuman 5)Crime Lord: ";
    std::cin >> typeChoice;
    std::cin.ignore(1000, '\n');

    std::cout << "ID: "; std::cin >> id;
    std::cin.ignore(1000, '\n');
    std::cout << "Codename: "; std::getline(std::cin, name);
    std::cout << "Rank (1-10): "; std::cin >> rank;
    std::cin.ignore(1000, '\n');

    std::shared_ptr<Criminal> newCrim;

    switch (typeChoice) {
    case 2: newCrim = std::make_shared<Hacker>(id, name, rank); break;
    case 3: newCrim = std::make_shared<BankRobber>(id, name, rank); break;
    case 4: newCrim = std::make_shared<MetaHuman>(id, name, rank); break;
    case 5: newCrim = std::make_shared<CrimeLord>(id, name, rank); break;
    default: newCrim = std::make_shared<Criminal>(id, name, rank); break;
    }

    database.push_back(newCrim);
    std::cout << "[SUCCESS] " << name << " added to database.\n";
}

void BatComputer::addNewFamilyMember() {
    std::string code, civil;
    int power, skillCount;
    std::vector<std::string> skills;

    std::cout << "\n--- ADD NEW FAMILY MEMBER ---\n";
    std::cout << "Codename: "; std::getline(std::cin, code);
    std::cout << "Civilian Name: "; std::getline(std::cin, civil);
    std::cout << "Physical Power Level: "; std::cin >> power;
    std::cout << "Number of skills: "; std::cin >> skillCount;
    std::cin.ignore(1000, '\n');

    for (int i = 0; i < skillCount; ++i) {
        std::string s;
        std::cout << "Skill " << i + 1 << ": ";
        std::getline(std::cin, s);
        skills.push_back(s);
    }

    auto newFam = std::make_shared<Family>(code, civil, power, skills);
    database.push_back(newFam);
    std::cout << "[SUCCESS] " << code << " added to Bat-Family files.\n";
}

void BatComputer::addNewBatsuitPart() {
    std::string partName;
    int level;
    double integrity;

    std::cout << "\n--- FORGE NEW BATSUIT COMPONENT ---\n";
    std::cout << "Component Name (ex: Reinforced Cowl): ";
    std::getline(std::cin, partName);

    std::cout << "Tech Level (1-10): ";
    if (!(std::cin >> level)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "[ERROR] Invalid level. Aborting.\n";
        return;
    }

    std::cout << "Initial Integrity % (default 100): ";
    if (!(std::cin >> integrity)) {
        integrity = 100.0;
        std::cin.clear();
    }
    std::cin.ignore(1000, '\n');

    auto newPart = std::make_shared<Batsuit>(level, partName, integrity);
    database.push_back(newPart);

    std::cout << "[SUCCESS] " << partName << " has been equipped to the Batsuit loadout.\n";
}

void BatComputer::simulateArkhamBlackout(double systemSecurity) {
    Criminal::simulateArkhamBlackout(this->database, systemSecurity);
}

void BatComputer::batcaveMaintenance(){
    Family::coordinateRepairs(this->database);
}

void BatComputer::generateCrimeReport() {
    Criminal::generateStrategicReport(this->database);
}

void BatComputer::runSiege() {
    Family::simulateSiege(this->database);
}

void BatComputer::runForensics() {
    Criminal::runForensics(this->database);
}
void BatComputer::runTraining(const std::string& name) {
    Family::runTrainingDay(this->database, name);
}
void BatComputer::runSuitRebalance() {
    Batsuit::redistributeIntegrity(this->database);
}

void BatComputer::checkSurvival(const std::string& enemy) {
    Batsuit::calculateSurvivalOdds(this->database, enemy);
}