#ifndef OPERATIONS_COORDINATOR_H
#define OPERATIONS_COORDINATOR_H

#include <vector>
#include <memory>
#include <string>
#include "../database_entry.h"

class OperationsCoordinator {
public:
    explicit OperationsCoordinator(std::vector<std::shared_ptr<DatabaseEntry>>& db);

    void simulateArkhamBlackout(double systemSecurity) const;
    void batcaveMaintenance() const;
    void generateCrimeReport() const;
    void runForensics() const;
    void runSiege() const;
    void runTraining(const std::string& name) const;
    void runSuitRebalance() const;
    void checkSurvival(const std::string& enemy) const;
    void runGlobalCyberDefense() const;
    void runUnderworldSting() const;
    void runGlobalTacticalSimulation() const;

private:
    std::vector<std::shared_ptr<DatabaseEntry>>& database;
};

#endif

