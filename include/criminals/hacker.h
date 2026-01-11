#ifndef HACKER_H
#define HACKER_H
#include "criminals.h"

class Hacker final : public Criminal {
protected:
    int bypassLevel;
public:
    explicit Hacker(const int id_ = 0, const std::string& name_ = "", const int rank_ = 1, const int bypass_ = 5)
        : Criminal(id_, name_, rank_, {}, CriminalType::HACKER), bypassLevel(bypass_) {}

    void hackSystem() const
    {
        std::cout << name << " is bypassing security with level " << bypassLevel << "!\n";
    }

    [[nodiscard]] double calculateThreatLevel() const override {
        return Criminal::calculateThreatLevel() + bypassLevel * 5;
    }

    [[nodiscard]] std::string type() const override { return "Hacker"; }

    void save(std::ostream& out) const override {
        Criminal::save(out);
        out << bypassLevel << "\n";
    }
};
#endif