#include "batsuit.h"
#include "../include/criminals/criminals.h"
#include <algorithm>
#include <sstream>

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

void Batsuit::applyBattleDamage(int damageBad) {
    integrity -= static_cast<double>(damageBad);
    if(integrity < 0.0) integrity = 0.0;
}

std::string Batsuit::interact(DatabaseEntry& other) {
    if(auto* cr = dynamic_cast<Criminal*>(&other)){
        // simple effect: if suit integrity low, criminal taunts, else suit intimidates
        if(integrity < 30.0) return name + " is damaged; " + cr->getName() + " mocks the weak suit.";
        return name + " intimidates " + cr->getName() + ", reducing threat.";
    }
    return name + " has no special interaction with " + other.type();
}
