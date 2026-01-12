#ifndef BATCOMPUTER_H
#define BATCOMPUTER_H

#include <vector>
#include <memory>
#include <string>
#include "database_entry.h"

class BatComputer {
private:
    static BatComputer* instance;
    BatComputer() = default;

protected:
    std::vector<std::shared_ptr<DatabaseEntry>> database;
    const std::string dbFilename = "database.txt";

public:

    static BatComputer& getInstance() {
        if (!instance) instance = new BatComputer();
        return *instance;
    }

    // --- GESTIUNE DATABASE ---
    void loadDatabase();
    void saveDatabase() const;
    void addEntity(const std::shared_ptr<DatabaseEntry>& entry) { database.push_back(entry); }
    void showAllCriminals() const;
    void showBatFamily() const;
    void showBatsuit() const;
    void showPolymorphicDatabase() const;
    void searchCriminal(const std::string& name) const;
    void promoteCriminal(const std::string& name) const;
    void analyzeMatchup(int idx1, int idx2) const;
    void simulateBattle(const std::string& familyMember, const std::string& criminalName) const;
    void performInteraction(int idx1, int idx2) const;
    void simulateEscape(const std::string& name, double securityLevel) const;
    void showCriminalIntel(const std::string& name) const;
    void addNewCriminal();
    void addNewFamilyMember();
    void addNewBatsuitPart();\
    void simulateArkhamBlackout(double systemSecurity);
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
};

#endif