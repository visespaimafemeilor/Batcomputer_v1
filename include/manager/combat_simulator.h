#ifndef COMBAT_SIMULATOR_H
#define COMBAT_SIMULATOR_H

#include <vector>
#include <memory>
#include <string>
#include "../database_entry.h"

class CombatSimulator {
public:
    explicit CombatSimulator(std::vector<std::shared_ptr<DatabaseEntry>>& db);

    void analyzeMatchup(int idx1, int idx2) const;
    void simulateBattle(const std::string& familyMember, const std::string& criminalName) const;
    void performInteraction(int idx1, int idx2) const;
    void simulateEscape(const std::string& name, double securityLevel) const;
    void showCriminalIntel(const std::string& name) const;

private:
    std::vector<std::shared_ptr<DatabaseEntry>>& database;
};

#endif

