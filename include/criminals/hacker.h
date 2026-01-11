#ifndef HACKER_H
#define HACKER_H
#include "criminals.h"

class Hacker : public Criminal {
private:
    int bypassLevel;
public:
    Hacker(int id_ = 0, std::string name_ = "", int rank_ = 1, int bypass_ = 5)
        : Criminal(id_, name_, rank_, {}, CriminalType::HACKER), bypassLevel(bypass_) {}

    // Funcție unică pentru Hacker
    void hackSystem() {
        std::cout << name << " is bypassing security with level " << bypassLevel << "!\n";
    }

    // Override pentru a schimba comportamentul
    double calculateThreatLevel() const override {
        return Criminal::calculateThreatLevel() + (bypassLevel * 5);
    }

    std::string type() const override { return "Hacker"; }

    // Trebuie să modificăm și save/load ca să includă bypassLevel
    void save(std::ostream& out) const override {
        Criminal::save(out);
        out << bypassLevel << "\n";
    }
};
#endif