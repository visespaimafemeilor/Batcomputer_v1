#include "family.h"
#include "batsuit.h"
#include "entry_factory.h"
#include <algorithm>
#include <limits>
#include <iostream>

#include "criminals/criminals.h"

int Family::familyMemberCount = 0;

Family::Family(const Family& other)
    : DatabaseEntry(other), civilian_name(other.civilian_name), physical_power(other.physical_power), skills(other.skills) { ++familyMemberCount; }

Family::~Family() { --familyMemberCount; }

void swap(Family& a, Family& b) noexcept {
    using std::swap;
    swap(a.name, b.name);
    swap(a.civilian_name, b.civilian_name);
    swap(a.physical_power, b.physical_power);
    swap(a.skills, b.skills);
}

Family& Family::operator=(Family other) {
    swap(*this, other);
    return *this;
}

std::unique_ptr<DatabaseEntry> Family::clone() const {
    return std::make_unique<Family>(*this);
}

void Family::doDisplay(std::ostream& os) const {
    os << "-- FAMILY: " << name << " (Civilian: " << civilian_name << ") --\n";
}

double Family::assessThreat() const {
    // threat based on physical power and number of skills
    return static_cast<double>(physical_power) * 5.0 + static_cast<double>(skills.size()) * 2.0;
}

std::string Family::type() const { return "Family"; }

std::string Family::summary() const { return "Family: " + name + " (" + civilian_name + ")"; }

bool Family::load(std::istream& in) {
    return loadFamilyMember(in);
}

void Family::save(std::ostream& out) const {
    out << 100 << "\n"; // ID-ul "100" inseamna mereu FAMILY
    out << name << "\n" << civilian_name << "\n" << physical_power << "\n";
    out << skills.size() << "\n";
    for(const auto& s : skills) out << s << "\n";
}

const std::string& Family::getCodename() const { return name; }
int Family::getPhysicalPower() const { return physical_power; }

bool Family::loadFamilyMember(std::istream& file) {
    if(!(file >> std::ws) || file.eof()) return false;
    if(!std::getline(file, name)) return false;
    if(!std::getline(file, civilian_name)) return false;
    if(!(file >> physical_power)) return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int skillCount = 0;
    if(!(file >> skillCount)) return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    skills.clear();
    for(int i = 0; i < skillCount; ++i) {
        std::string line;
        if(!std::getline(file, line)) return false;
        skills.push_back(line);
    }
    return true;
}

void Family::showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db) {
    std::cout << "\n=== BAT-FAMILY FILES ===\n";
    bool found = false;

    for (const auto& e : db) {
        if (const Family* f = e->asFamily()) {
            f->displayInfo();
            std::cout << "Power Level: " << f->getPhysicalPower() << "\n";

            std::cout << "--------------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No Bat-Family members detected in current records.\n";
    }
}

bool Family::fight(const Criminal& enemy) const {
    const int powerScore = physical_power + static_cast<int>(skills.size()) * 2;
    const int enemyScore = enemy.getRank() * 3;
    return powerScore >= enemyScore;
}

std::string Family::fightReport(const Criminal& enemy) const {
    const bool win = fight(enemy);
    std::string res = name + " vs " + enemy.getName() + ": ";
    res += win ? "WIN" : "LOSE";
    res += " (Power: " + std::to_string(physical_power) + ", Rank: " + std::to_string(enemy.getRank()) + ")\n";
    return res;
}

std::string Family::simulateBattle(const Criminal& enemy) const {
    const int skillBonus = static_cast<int>(skills.size());
    const int odds = physical_power + skillBonus - enemy.getRank() * 2;
    if(odds > 5) return "Decisive victory for " + name + "\n";
    if(odds > 0) return "Close win for " + name + "\n";
    if(odds == 0) return "Draw between " + name + " and " + enemy.getName() + "\n";
    return "Narrow loss for " + name + "\n";
}

std::string Family::interact(DatabaseEntry& other) {
    if(const std::string resp = other.interactedBy(*this); !resp.empty()) return resp;
    return name + " has no special interaction with " + other.type();
}

std::string Family::interactedBy(const Criminal& c) {
    if(fight(c)) return name + " confronts " + c.getName() + " and wins!";
    return name + " confronts " + c.getName() + " and loses.";
}

std::string Family::interactedBy(const Batsuit& b) {
    (void)b;
    return {};
}

void Family::coordinateRepairs(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    bool oraclePresent = false;
    double repairPower = 15.0;

    // Pasul 1: Verificam dacă Oracle este in baza de date
    for (const auto& entry : database) {
        if (const Family* f = entry->asFamily()) {
            if (f->getName() == "Oracle") {
                oraclePresent = true;
                repairPower = 40.0; // Dacă Oracle ajuta, reparatiile sunt mult mai bune
                std::cout << "[SYSTEM] Oracle is remote-linking to the Batcave. Repair efficiency at maximum!\n";
                break;
            }
        }
    }

    if (!oraclePresent) {
        std::cout << "[WARNING] Oracle not online. Using automated backup systems (Low Efficiency).\n";
    }

    // Pasul 2: Reparam piesele
    int repairedCount = 0;
    for (auto& entry : database) {
        if (Batsuit* suitPart = entry->asBatsuit()) {
            suitPart->applyBattleDamage(static_cast<int>(-repairPower));
            std::cout << "[FIXED] " << suitPart->getName()
                      << " restored to " << suitPart->getIntegrity() << "%\n";
            repairedCount++;
        }
    }

    if (repairedCount == 0) {
        std::cout << "[INFO] No Batsuit components found in database to repair.\n";
    } else {
        std::cout << "[COMPLETE] Maintenance finished for " << repairedCount << " components.\n";
    }
}

void Family::simulateSiege(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    double totalDefense = 0;
    double totalAttack = 0;

    std::cout << "\n[!!!] GOTHAM UNDER SIEGE: ALL-OUT WAR [!!!]\n";

    for (const auto& e : database) {
        if (const Family* f = e->asFamily()) {
            totalDefense += f->getPhysicalPower();
            std::cout << "[DEFENDER] " << f->getName() << " is on position." << "\n";
        } else if (const Criminal* c = e->asCriminal()) {
            totalAttack += c->calculateThreatLevel();
            std::cout << "[ATTACKER] " << c->getName() << " is advancing." << "\n";
        }
    }

    std::cout << "\nTotal Defense Power: " << totalDefense << "\n";
    std::cout << "Total Attack Power: " << totalAttack << "\n";

    if (totalDefense >= totalAttack) {
        std::cout << "RESULT: THE LINE HELD. Gotham remains under protection.\n";
    } else {
        std::cout << "RESULT: BREACH! The city has fallen to the criminal underworld.\n";
    }
}

void Family::runTrainingDay(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const std::string& memberName) {
    bool batmanPresent = false;
    for (const auto& e : database) {
        if (e->getName() == "Batman") { batmanPresent = true; break; }
    }

    for (auto& e : database) {
        if (Family* f = e->asFamily()) {
            if (f->getCodename() == memberName) {
                const int boost = batmanPresent ? 25 : 10;
                f->physical_power += boost;
                std::cout << "[TRAINING] " << memberName << " trained "
                          << (batmanPresent ? "with Batman" : "alone")
                          << ". Power increased by " << boost << "!\n";
                return;
            }
        }
    }
    std::cout << "Member not found.\n";
}
