#include "criminals/metahuman.h"
#include "batsuit.h"
#include <memory>

MetaHuman::MetaHuman(const int id_, const std::string& name_, const int rank_, std::string source, const double scale)
    : Criminal(id_, name_, rank_, {}, CriminalType::METAHUMAN), 
      powerSource(std::move(source)), powerScale(scale) {}

std::unique_ptr<DatabaseEntry> MetaHuman::clone() const {
    return std::make_unique<MetaHuman>(*this);
}

void MetaHuman::doDisplay(std::ostream& os) const {
    Criminal::doDisplay(os);
    os << " | POWER SOURCE: " << powerSource << " (Scale: " << powerScale << ")\n";
}

double MetaHuman::calculateThreatLevel() const {
    return Criminal::calculateThreatLevel() * powerScale + 50.0;
}

std::string MetaHuman::type() const { return "Meta-Human"; }

std::string MetaHuman::specialty() const {
    return "Superhuman Ability: " + powerSource;
}

void MetaHuman::save(std::ostream& out) const {
    Criminal::save(out);
    out << powerSource << "\n" << powerScale << "\n";
}

bool MetaHuman::load(std::istream& in) {
    if (!Criminal::load(in)) return false;
    in >> powerSource >> powerScale;
    return true;
}

void MetaHuman::onGlobalTacticalSimulation(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const {
    std::cout << "[!] MASSIVE THREAT: " << name << " is using " << type() << " powers!\n";
    for (auto& e : database) {
        if (const auto suit = std::dynamic_pointer_cast<Batsuit>(e)) {
            suit->applyBattleDamage(10.0);
        }
    }
}
