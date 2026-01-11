#ifndef CRIME_LORD_H
#define CRIME_LORD_H
#include "criminals.h"

class CrimeLord : public Criminal {
public:
    using Criminal::Criminal; // Moștenește constructorii

    // Abilitate specială: Crește rank-ul altor criminali
    void inspireThugs(std::vector<std::unique_ptr<Criminal>>& others) {
        std::cout << name << " is rallying the troops!\n";
        for(auto& c : others) {
            if(c->getId() != this->id) c->promote(1);
        }
    }

    double calculateThreatLevel() const override {
        return Criminal::calculateThreatLevel() * 2.0;
    }

    std::string type() const override { return "Crime Lord"; }
};
#endif