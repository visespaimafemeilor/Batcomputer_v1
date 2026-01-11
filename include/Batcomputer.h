#ifndef BATCOMPUTER_H
#define BATCOMPUTER_H

#include <vector>
#include <memory>
#include <string>
#include "database_entry.h"

class BatComputer {
private:
    std::vector<std::shared_ptr<DatabaseEntry>> database;
    const std::string dbFilename = "database.txt";

public:
    // --- GESTIUNE DATABASE ---
    void loadDatabase();
    void saveDatabase();
    void addEntity(const std::shared_ptr<DatabaseEntry>& entry) { database.push_back(entry); }
    void showAllCriminals() const;
    void showBatFamily() const;
    void showBatsuit() const;
    void showPolymorphicDatabase() const;
    void searchCriminal(const std::string& name) const;
    void promoteCriminal(const std::string& name);
    void simulateBattle(const std::string& familyMember, const std::string& criminalName);
    void performInteraction(int idx1, int idx2);
    void simulateEscape(const std::string& name, double securityLevel) const;
    void showCriminalIntel(const std::string& name) const;
    void addNewCriminal();
    void addNewFamilyMember();
    void addNewBatsuitPart();\
    void simulateArkhamBlackout(double systemSecurity);
    void batcaveMaintenance();
    void generateCrimeReport();
    void runForensics();
    void runSiege();
    void runTraining(const std::string& name);
    void runSuitRebalance();
    void checkSurvival(const std::string& enemy);
};

#endif