#include "../../include/manager/operations_coordinator.h"
#include "criminals/hacker.h"
#include "criminals/crimeLord.h"
#include "criminals/metahuman.h"
#include "family.h"
#include "batsuit.h"
#include "criminals/criminals.h"
#include <iostream>

OperationsCoordinator::OperationsCoordinator(std::vector<std::shared_ptr<DatabaseEntry>>& db)
    : database(db) {}

void OperationsCoordinator::simulateArkhamBlackout(const double systemSecurity) const
{
    Criminal::simulateArkhamBlackout(this->database, systemSecurity);
}

void OperationsCoordinator::batcaveMaintenance() const {
    Family::coordinateRepairs(this->database);
}

void OperationsCoordinator::generateCrimeReport() const {
    Criminal::generateStrategicReport(this->database);
}

void OperationsCoordinator::runForensics() const {
    Criminal::runForensics(this->database);
}

void OperationsCoordinator::runSiege() const {
    Family::simulateSiege(this->database);
}

void OperationsCoordinator::runTraining(const std::string& name) const {
    Family::runTrainingDay(this->database, name);
}

void OperationsCoordinator::runSuitRebalance() const {
    Batsuit::redistributeIntegrity(this->database);
}

void OperationsCoordinator::checkSurvival(const std::string& enemy) const {
    Batsuit::calculateSurvivalOdds(this->database, enemy);
}

void OperationsCoordinator::runGlobalCyberDefense() const {
    std::cout << "\n[SYSTEM] SCANNING FOR ACTIVE CYBER THREATS...\n";
    bool threatFound = false;

    for (auto& entry : database) {
        if (const auto hacker = std::dynamic_pointer_cast<Hacker>(entry)) {
            hacker->hackSystem(this->database);
            threatFound = true;
        }
    }

    if (!threatFound) {
        std::cout << "[SUCCESS] No active hackers detected. Bat-Network is stable.\n";
    }
}

void OperationsCoordinator::runUnderworldSting() const {
    std::cout << "\n[SYSTEM] MONITORING CRIME LORD INFLUENCE...\n";
    bool bossFound = false;

    for (auto& entry : database) {
        if (const auto lord = std::dynamic_pointer_cast<CrimeLord>(entry)) {
            lord->inspireThugs(this->database);
            bossFound = true;
        }
    }

    if (!bossFound) {
        std::cout << "[INFO] No major crime lords are currently rallying troops.\n";
    }
}

void OperationsCoordinator::runGlobalTacticalSimulation() const {
    std::cout << "\n=== [BAT-COMPUTER] STARTING GLOBAL TACTICAL SIMULATION ===\n";

    for (auto& entry : database) {
        if (const auto hacker = std::dynamic_pointer_cast<Hacker>(entry)) {
            hacker->hackSystem(database);
            continue;
        }

        if (const auto lord = std::dynamic_pointer_cast<CrimeLord>(entry)) {
            lord->inspireThugs(database);
            continue;
        }

        if (const auto meta = std::dynamic_pointer_cast<MetaHuman>(entry)) {
            std::cout << "[!] MASSIVE THREAT: " << meta->getName()
                      << " is using " << meta->type() << " powers!\n";
            for (auto& e : database) {
                if (const auto suit = std::dynamic_pointer_cast<Batsuit>(e)) {
                    suit->applyBattleDamage(10.0);
                }
            }
        }
    }
    std::cout << "=== SIMULATION CONCLUDED ===\n";
}
