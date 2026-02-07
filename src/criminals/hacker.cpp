#include "criminals/hacker.h"
#include "batsuit.h"
#include <iostream>

Hacker::Hacker(const int id_, const std::string& name_, const int rank_, const int bypass_)
    : Criminal(id_, name_, rank_, {}, CriminalType::HACKER), bypassLevel(bypass_) {}

std::unique_ptr<DatabaseEntry> Hacker::clone() const {
    return std::make_unique<Hacker>(*this);
}

void Hacker::doDisplay(std::ostream& os) const {
    Criminal::doDisplay(os);
    os << " | Specialty: Digital Sabotage (Bypass Level: " << bypassLevel << ")\n";
}
void Hacker::hackSystem(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const {
    std::cout << "\n[!] CYBER-ATTACK: " << name << " (Bypass Lvl: " << bypassLevel 
              << ") is uploading a virus to the Bat-Network!\n";
    
    bool hitAny = false;
    for (auto& entry : database) {
        if (Batsuit* suitPart = entry->asBatsuit()) {
            const double damage = 2.0 * bypassLevel;
            suitPart->applyBattleDamage(static_cast<int>(damage));
            
            std::cout << "    > Exploit found in " << suitPart->getName() 
                      << "! Integrity decreased by " << damage << "%\n";
            hitAny = true;
        }
    }
    if (!hitAny) std::cout << "    > No vulnerable Bat-Tech detected in range.\n";
}

double Hacker::calculateThreatLevel() const {
    return Criminal::calculateThreatLevel() + bypassLevel * 5.0;
}

std::string Hacker::type() const {
    return {"Hacker"};
}

void Hacker::save(std::ostream& out) const {
    Criminal::save(out);
    out << bypassLevel << "\n";
}