#include "../../include/manager/combat_simulator.h"
#include "criminals/criminals.h"
#include "family.h"
#include "criminals/hacker.h"
#include <iostream>

#include "exceptions.h"

CombatSimulator::CombatSimulator(std::vector<std::shared_ptr<DatabaseEntry>>& db)
    : database(db) {}

void CombatSimulator::analyzeMatchup(const int idx1, const int idx2) const {
    if (idx1 < 0 || idx1 >= static_cast<int>(database.size()) || idx2 < 0 || idx2 >= static_cast<int>(database.size())) {
        throw DatabaseOperationException("Failed analyzeMatchup");
    }

    const auto obj1 = database[idx1];
    if (const auto obj2 = database[idx2]; compareEfficiency(*obj1, *obj2)) {
        std::cout << obj1->getName() << " Has a greater influence than " << obj2->getName() << "\n";
    } else {
        std::cout << obj2->getName() << " dominates from a tactical perspective.\n";
    }
}

void CombatSimulator::simulateBattle(const std::string&, const std::string&) const {
    std::shared_ptr<Family> vigilante = nullptr;
    std::shared_ptr<Criminal> enemy = nullptr;

    for (auto& e : database) {
        if (!vigilante) vigilante = std::dynamic_pointer_cast<Family>(e);
        if (!enemy) enemy = std::dynamic_pointer_cast<Criminal>(e);
        if (vigilante && enemy) break;
    }

    if (vigilante && enemy) {
        std::cout << "\n--- BATTLE SIMULATION ---\n";
        std::cout << vigilante->fightReport(*enemy);
        std::cout << vigilante->simulateBattle(*enemy);
    } else {
        std::cout << "Simulation failed: Target(s) not found.\n";
    }
}

void CombatSimulator::performInteraction(const int idx1, const int idx2) const {
    if (idx1 >= 0 && static_cast<size_t>(idx1) < database.size() && idx2 >= 0 && static_cast<size_t>(idx2) < database.size()) {
        std::cout << "Result: " << database[idx1]->interact(*database[idx2]) << "\n";
    } else {
        std::cout << "Invalid indices for interaction.\n";
    }
}

void CombatSimulator::simulateEscape(const std::string& name, const double securityLevel) const {
    for (const auto& e : database) {
        if (const Criminal* c = e->asCriminal()) {
            if (c->getName() == name) {
                const bool escaped = c->simulateEscape(securityLevel);
                std::cout << (escaped ? "ESCAPED!" : "Contained.") << "\n";
                return;
            }
        }
    }
    std::cout << "Criminal not found.\n";
}

void CombatSimulator::showCriminalIntel(const std::string& name) const {
    for (const auto& e : database) {
        if (const Criminal* c = e->asCriminal()) {
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
