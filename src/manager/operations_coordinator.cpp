#include "manager/operations_coordinator.h"
#include "criminals/hacker.h"
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

    for (const auto& entry : database) {
        if (const Criminal* c = entry->asCriminal()) {
            c->onCyberSweep(this->database);
            if (c->hackerCountContribution() > 0) threatFound = true;
        }
    }

    if (!threatFound) {
        std::cout << "[SUCCESS] No active hackers detected. Bat-Network is stable.\n";
    }
}

void OperationsCoordinator::runUnderworldSting() const {
    std::cout << "\n[SYSTEM] MONITORING CRIME LORD INFLUENCE...\n";
    bool bossFound = false;

    for (const auto& entry : database) {
        if (const Criminal* c = entry->asCriminal()) {
            c->onUnderworldSting(this->database);
            if (c->leaderInfluenceContribution() > 0) bossFound = true;
        }
    }

    if (!bossFound) {
        std::cout << "[INFO] No major crime lords are currently rallying troops.\n";
    }
}

void OperationsCoordinator::runGlobalTacticalSimulation() const {
    std::cout << "\n=== [BAT-COMPUTER] STARTING GLOBAL TACTICAL SIMULATION ===\n";

    for (const auto& entry : database) {
        if (const Criminal* c = entry->asCriminal()) {
            c->onGlobalTacticalSimulation(database);
        }
    }
    std::cout << "=== SIMULATION CONCLUDED ===\n";
}
