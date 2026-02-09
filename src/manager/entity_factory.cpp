#include "manager/entity_factory.h"
#include "criminals/hacker.h"
#include "criminals/bank_robber.h"
#include "criminals/metahuman.h"
#include "criminals/crimeLord.h"
#include "family.h"
#include "batsuit.h"
#include <iostream>

EntityFactory::EntityFactory(std::vector<std::shared_ptr<DatabaseEntry>>& db)
    : database(db) {}

void EntityFactory::addNewCriminal() const
{
    std::string name;
    int id = 0, rank = 1, typeChoice = 0;

    std::cout << "\n--- ADD NEW CRIMINAL ---\n";
    std::cout << "Select Type: 1) Generic 2) Hacker 3) Bank Robber 4) MetaHuman 5)Crime Lord: ";
    if (!(std::cin >> typeChoice)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "[ERROR] Invalid type selection. Aborting add operation.\n";
        return;
    }
    std::cin.ignore(1000, '\n');

    std::cout << "ID: ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "[ERROR] Invalid ID. Aborting add operation.\n";
        return;
    }
    std::cin.ignore(1000, '\n');

    std::cout << "Codename: ";
    std::getline(std::cin, name);
    if (name.empty()) {
        std::cout << "[ERROR] Empty codename provided. Aborting add operation.\n";
        return;
    }

    std::cout << "Rank (1-10): ";
    if (!(std::cin >> rank)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "[ERROR] Invalid rank. Aborting add operation.\n";
        return;
    }
    std::cin.ignore(1000, '\n');

    // Sanitize rank range
    if (rank < 1) rank = 1;
    if (rank > 10) rank = 10;

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

void EntityFactory::addNewFamilyMember() const
{
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

    const auto newFam = std::make_shared<Family>(code, civil, power, skills);
    database.push_back(newFam);
    std::cout << "[SUCCESS] " << code << " added to Bat-Family files.\n";
}

void EntityFactory::addNewBatsuitPart() const
{
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

    const auto newPart = std::make_shared<Batsuit>(level, partName, integrity);
    database.push_back(newPart);

    std::cout << "[SUCCESS] " << partName << " has been equipped to the Batsuit loadout.\n";
}
