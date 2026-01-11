#ifndef CRIME_LORD_H
#define CRIME_LORD_H
#include "criminals.h"

class CrimeLord final : public Criminal {
public:
    using Criminal::Criminal; // Moștenește constructorii

    // Abilitate specială: Crește rank-ul altor criminali
    void inspireThugs(const std::vector<std::unique_ptr<Criminal>>& others) const
    {
        std::cout << name << " is rallying the troops!\n";
        for(auto& c : others) {
            if(c->getId() != this->id) c->promote(1);
        }
    }

    [[nodiscard]] double calculateThreatLevel() const override {
        return Criminal::calculateThreatLevel() * 2.0;
    }

    [[nodiscard]] std::string type() const override { return "Crime Lord"; }
};
#endif