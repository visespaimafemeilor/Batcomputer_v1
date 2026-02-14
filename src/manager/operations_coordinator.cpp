#include "manager/operations_coordinator.h"
#include "family.h"
#include "batsuit.h"
#include "criminals/hacker.h"
#include "criminals/icriminal_cyber.h"
#include "criminals/icriminal_leader.h"
#include "criminals/icriminal_tactical.h"
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
            if (auto* ic = dynamic_cast<const ICyberThreat*>(c)) {
                ic->onCyberSweep(this->database);
                if (ic->hackerCountContribution() > 0) threatFound = true;
            }
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
            if (auto* il = dynamic_cast<const ILeaderInfluence*>(c)) {
                il->onUnderworldSting(this->database);
                if (il->leaderInfluenceContribution() > 0) bossFound = true;
            }
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
            if (auto* it = dynamic_cast<const ITacticalSimulator*>(c)) {
                it->onGlobalTacticalSimulation(database);
            }
        }
    }
    std::cout << "=== SIMULATION CONCLUDED ===\n";
}
