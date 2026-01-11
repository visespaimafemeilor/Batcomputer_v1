#include "family.h"
#include "batsuit.h"
#include <algorithm>
#include <limits>
#include <iostream>

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

void Family::displayInfo() const {
    std::cout << "-- FAMILY: " << name << " (Civilian: " << civilian_name << ") --\n";
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
const std::string& Family::getCivilianName() const { return civilian_name; }
int Family::getPhysicalPower() const { return physical_power; }
const std::vector<std::string>& Family::getSkills() const { return skills; }

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

bool Family::fight(const Criminal& enemy) const {
    int powerScore = physical_power + static_cast<int>(skills.size()) * 2;
    int enemyScore = enemy.getRank() * 3;
    return powerScore >= enemyScore;
}

std::string Family::fightReport(const Criminal& enemy) const {
    bool win = fight(enemy);
    std::string res = name + " vs " + enemy.getName() + ": ";
    res += (win ? "WIN" : "LOSE");
    res += " (Power: " + std::to_string(physical_power) + ", Rank: " + std::to_string(enemy.getRank()) + ")\n";
    return res;
}

std::string Family::simulateBattle(const Criminal& enemy) const {
    int skillBonus = static_cast<int>(skills.size());
    int odds = physical_power + skillBonus - (enemy.getRank() * 2);
    if(odds > 5) return "Decisive victory for " + name + "\n";
    if(odds > 0) return "Close win for " + name + "\n";
    if(odds == 0) return "Draw between " + name + " and " + enemy.getName() + "\n";
    return "Narrow loss for " + name + "\n";
}

std::string Family::interact(DatabaseEntry& other) {
    if(auto* cr = dynamic_cast<Criminal*>(&other)){
        if(fight(*cr)) return name + " confronts " + cr->getName() + " and wins!";
        else return name + " confronts " + cr->getName() + " and loses.";
    }
    return name + " has no special interaction with " + other.type();
}

void Family::coordinateRepairs(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    bool oraclePresent = false;
    double repairPower = 15.0;

    // Pasul 1: Verificam dacă Oracle este in baza de date
    for (const auto& entry : database) {
        if (auto f = std::dynamic_pointer_cast<Family>(entry)) {
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
        if (auto suitPart = std::dynamic_pointer_cast<Batsuit>(entry)) {
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