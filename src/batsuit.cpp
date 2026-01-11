#include "batsuit.h"
#include "../include/criminals/criminals.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

int Batsuit::suitPartCount = 0;

Batsuit::Batsuit(int level_, std::string part_, double integrity_)
    : DatabaseEntry(std::move(part_)), level(level_), integrity(integrity_)
{
    normalize();
    ++suitPartCount;
}

Batsuit::~Batsuit() { --suitPartCount; }

void Batsuit::normalize() {
    if(integrity < 0.0) integrity = 0.0;
    if(integrity > 100.0) integrity = 100.0;
    if(level < 0) level = 0;
}

double Batsuit::assessThreat() const {
    // less threatening when in poor condition
    return static_cast<double>(level) * (integrity / 100.0) * 2.5;
}

std::unique_ptr<DatabaseEntry> Batsuit::clone() const {
    return std::make_unique<Batsuit>(*this);
}

std::string Batsuit::type() const { return "Batsuit"; }

std::string Batsuit::summary() const { return "Batsuit part: " + name + " (Level: " + std::to_string(level) + ")"; }

bool Batsuit::load(std::istream& in) {
    return loadBatsuit(in);
}

void Batsuit::save(std::ostream& out) const {
    out << 200 << "\n"; // ID-ul "200" inseamna mereu BATSUIT
    out << name << "\n" << level << "\n" << integrity << "\n";
}

void Batsuit::showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db) {
    std::cout << "\n=== BATSUIT INTEGRITY REPORT ===\n";
    bool found = false;

    for (const auto& e : db) {
        if (auto b = std::dynamic_pointer_cast<Batsuit>(e)) {
            std::cout << b->statusReport() << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "[SYSTEM] No Batsuit components found in active loadout.\n";
    }
}

Batsuit::Batsuit(const Batsuit& other)
    : DatabaseEntry(other), level(other.level), integrity(other.integrity)
{ ++suitPartCount; }

void swap(Batsuit& a, Batsuit& b) noexcept {
    using std::swap;
    swap(a.name, b.name);
    swap(a.level, b.level);
    swap(a.integrity, b.integrity);
}

Batsuit& Batsuit::operator=(Batsuit other) {
    swap(*this, other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Batsuit& bs) {
    os << "Part: " << bs.name << " | Level: " << bs.level << " | Integrity: " << bs.integrity << "%";
    return os;
}

[[nodiscard]] int Batsuit::getLevel() const { return level; }

[[nodiscard]] const std::string& Batsuit::getPart() const { return name; }

[[nodiscard]] double Batsuit::getIntegrity() const { return integrity; }

bool Batsuit::loadBatsuit(std::istream& file) {
    if(!(std::getline(file, name))) return false;
    if(!(file >> level)) return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(!(file >> integrity)) return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    normalize();
    return true;
}

[[nodiscard]] bool Batsuit::isCritical(double threshold) const {
    return integrity < threshold;
}

[[nodiscard]] std::string Batsuit::statusReport() const {
    std::ostringstream ss;
    ss << "Part: " << name << " | Level: " << level << " | Integrity: " << integrity << "%";
    if(isCritical()) ss << " [CRITICAL]";
    return ss.str();
}

void Batsuit::applyBattleDamage(double damageBad) {
    integrity -= static_cast<double>(damageBad);
    if(integrity < 0.0) integrity = 0.0;
}

std::string Batsuit::interact(DatabaseEntry& other) {
    if(const auto* cr = dynamic_cast<Criminal*>(&other)){
        // simple effect: if suit integrity low, criminal taunts, else suit intimidates
        if(integrity < 30.0) return name + " is damaged; " + cr->getName() + " mocks the weak suit.";
        return name + " intimidates " + cr->getName() + ", reducing threat.";
    }
    return name + " has no special interaction with " + other.type();
}

void Batsuit::redistributeIntegrity(std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    std::vector<std::shared_ptr<Batsuit>> parts;
    double totalIntegrity = 0;

    for (auto& e : database) {
        if (auto b = std::dynamic_pointer_cast<Batsuit>(e)) {
            parts.push_back(b);
            totalIntegrity += b->getIntegrity();
        }
    }

    if (parts.empty()) return;

    const double average = totalIntegrity / parts.size();
    std::cout << "\n[BAT-SYSTEMS] Rebalancing Integrity. Target Average: " << average << "%\n";

    for (const auto& p : parts) {
        if (p->getIntegrity() > average) {
            const double surplus = (p->getIntegrity() - average) * 0.5;
            p->applyBattleDamage(surplus);
        } else {
            const double deficit = (average - p->getIntegrity()) * 0.5;
            p->applyBattleDamage(-deficit);
        }
        std::cout << "  > " << p->getName() << " stabilized at " << p->getIntegrity() << "%\n";
    }
}

void Batsuit::calculateSurvivalOdds(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const std::string& enemyName) {
    double techSum = 0;
    double harmonicIntegritySum = 0;
    int count = 0;
    double enemyThreat = 0;

    // 1. Găsim inamicul
    for (const auto& e : database) {
        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
            if (c->getName() == enemyName) {
                enemyThreat = c->calculateThreatLevel();
                break;
            }
        }
    }

    // 2. Calculăm parametrii costumului
    for (const auto& e : database) {
        if (auto b = std::dynamic_pointer_cast<Batsuit>(e)) {
            techSum += b->getLevel();
            // Folosim media armonică pentru a penaliza sever dacă o singură piesă e aproape de 0
            harmonicIntegritySum += 1.0 / (b->getIntegrity() + 1.0);
            count++;
        }
    }

    if (count == 0 || enemyThreat == 0) {
        std::cout << "Incomplete data for simulation.\n";
        return;
    }

    double avgTech = techSum / count;
    double suitHealth = count / harmonicIntegritySum;

    double winChance = (suitHealth * (avgTech / 10.0)) / (enemyThreat / 50.0);
    if (winChance > 100.0) winChance = 100.0;

    std::cout << "\n--- COMBAT PROBABILITY REPORT ---\n";
    std::cout << "Enemy: " << enemyName << " (Threat: " << enemyThreat << ")\n";
    std::cout << "Suit Efficiency (Harmonic): " << suitHealth << "%\n";
    std::cout << "Calculated Win Chance: " << std::fixed << std::setprecision(2) << winChance << "%\n";

    if (winChance < 30.0) std::cout << "ADVICE: DO NOT ENGAGE. Suit failure imminent.\n";
    else if (winChance < 70.0) std::cout << "ADVICE: Proceed with caution. High risk of armor breach.\n";
    else std::cout << "ADVICE: Optimal conditions for engagement.\n";
}