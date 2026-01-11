#ifndef HACKER_H
#define HACKER_H

#include "criminals.h"

class Hacker : public Criminal {
public:
    explicit Hacker(int id_ = 0, std::string name_ = "", int rank_ = 1, const std::vector<std::string>& intel_ = {})
        : Criminal(id_, std::move(name_), rank_, intel_) {}
    ~Hacker() override = default;

    double calculateThreatLevel() const override {
        double base = Criminal::calculateThreatLevel();
        double bonus = 0.0;
        for (const auto &s : getIntel()) if (s.find("exploit") != std::string::npos) bonus += 4.0;
        return base + bonus;
    }

    std::unique_ptr<DatabaseEntry> clone() const override { return std::make_unique<Hacker>(*this); }
    std::string type() const override { return std::string("Hacker"); }
    std::string summary() const override { return std::string("Hacker: " + getName() + " (Rank: " + std::to_string(getRank()) + ")"); }
};

#endif // HACKER_H

