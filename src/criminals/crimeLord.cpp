#include "criminals/crimeLord.h"
#include <iostream>

CrimeLord::CrimeLord(const int id_, const std::string& name_, const int rank_)
    : Criminal(id_, name_, rank_, {}, CriminalType::CRIME_LORD) {}

std::unique_ptr<DatabaseEntry> CrimeLord::clone() const {
    return std::make_unique<CrimeLord>(*this);
}

void CrimeLord::doDisplay(std::ostream& os) const {
    Criminal::doDisplay(os);
    os << " | Status: Crime Lord (Force Multiplier Active)\n";
}

void CrimeLord::inspireThugs(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const {
    std::cout << "\n[!] UNDERWORLD RALLY: Crime Lord " << name << " is inspiring the troops!\n";
    
    int count = 0;
    for (auto& entry : database) {
        if (Criminal* other = entry->asCriminal()) {
            if (other->getId() != this->id) {
                other->promote(1);
                std::cout << "    > " << other->getName() << " inspired! New Rank: " << other->getRank() << "\n";
                count++;
            }
        }
    }
    
    if (count == 0) {
        std::cout << "    > No thugs found to rally.\n";
    }
}

double CrimeLord::calculateThreatLevel() const {
    return Criminal::calculateThreatLevel() * 2.0;
}

std::string CrimeLord::type() const {
    return {"Crime Lord"};
}