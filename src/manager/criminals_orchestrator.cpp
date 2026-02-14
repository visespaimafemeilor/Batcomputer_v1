#include "manager/criminals_orchestrator.h"
#include "criminals/criminals.h"
#include "criminals/icriminal_cyber.h"
#include "criminals/icriminal_leader.h"
#include "family.h"
#include "batsuit.h"
#include <iostream>

namespace manager {

void simulateArkhamBlackout(std::vector<std::shared_ptr<DatabaseEntry>>& database, const double systemSecurity) {
    std::cout << "\n!!! [ALARM] ARCHAM ASYLUM SYSTEM BREACH DETECTED !!!\n";

    double finalSecurity = systemSecurity;
    for (const auto& entry : database) {
        if (const Criminal* c = entry->asCriminal()) {
            if (auto* il = dynamic_cast<const ILeaderInfluence*>(c)) {
                il->affectBlackoutSecurity(finalSecurity);
            }
        }
    }

    auto it = database.begin();
    int escapeCount = 0;

    while (it != database.end()) {
        if (const Criminal* c = (*it)->asCriminal()) {
            if (c->simulateEscape(finalSecurity)) {
                std::cout << "[OUTBREAK] " << c->getName() << " (Rank " << c->getRank() << ") has escaped!\n";
                it = database.erase(it);
                escapeCount++;
                continue;
            }
        }
        ++it;
    }

    std::cout << "\n[REPORT] Outbreak contained. Total escaped: " << escapeCount << "\n";
    if (escapeCount > 0) std::cout << "[WARNING] Gotham PD warns citizens to stay indoors.\n";
}

void generateStrategicReport(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    double totalCriminalThreat = 0;
    double totalFamilyDefense = 0;
    int hackerCount = 0;
    bool oraclePresent = false;
    int brokenParts = 0;

    std::cout << "\n--- [BAT-COMPUTER STRATEGIC ANALYSIS] ---\n";

    for (const auto& entry : database) {
        if (const Criminal* c = entry->asCriminal()) {
            totalCriminalThreat += c->calculateThreatLevel();
            if (auto* ic = dynamic_cast<const ICyberThreat*>(c)) {
                hackerCount += ic->hackerCountContribution();
            }
        }
        else if (const Family* f = entry->asFamily()) {
            totalFamilyDefense += f->getPhysicalPower();
            if (f->getName() == "Oracle") oraclePresent = true;
        }
        else if (const Batsuit* b = entry->asBatsuit()) {
            if (b->getIntegrity() < 50.0) brokenParts++;
        }
    }

    if (hackerCount > 0 && !oraclePresent) {
        totalCriminalThreat *= 1.3;
        std::cout << "[!] WARNING: Digital vulnerability detected. Hackers are unmonitored!\n";
    }

    if (brokenParts > 2) {
        totalFamilyDefense *= 0.8;
        std::cout << "[!] WARNING: Batsuit integrity is compromised. Frontline efficiency lowered.\n";
    }

    std::cout << "\nGlobal Threat Level: " << totalCriminalThreat << "\n";
    std::cout << "Global Defense Level: " << totalFamilyDefense << "\n";

    const double ratio = totalCriminalThreat / (totalFamilyDefense + 1.0);

    std::cout << "STATUS: ";
    if (ratio < 0.5) std::cout << "GOTHAM IS SECURE. Batman has the situation under control.\n";
    else if (ratio < 1.2) std::cout << "EQUILIBRIUM. Constant vigilance required.\n";
    else if (ratio < 2.0) std::cout << "DANGER. Criminal activity outpaces response capabilities!\n";
    else std::cout << "CRITICAL. Gotham is falling. Call the Justice League.\n";
}

void runForensics(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    bool oracleProtects = false;
    for (const auto& e : database) {
        if (const Family* f = e->asFamily()) {
            if (f->getName() == "Oracle") oracleProtects = true;
        }
    }

    std::cout << "\n--- DIGITAL FORENSICS REPORT ---\n";
    if (oracleProtects) {
        std::cout << "[SAFE] Oracle has encrypted all Bat-Systems. Hackers are powerless.\n";
        return;
    }

    for (const auto& e : database) {
        if (const Criminal* c = e->asCriminal()) {
            if (auto* ic = dynamic_cast<const ICyberThreat*>(c)) {
                ic->runForensicsAction(database);
            }
        }
    }
}

} // namespace manager

