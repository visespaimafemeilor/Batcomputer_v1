#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "criminals.h"

class Mastermind : public Criminal {
public:
    explicit Mastermind(int id_ = 1, std::string name_ = "mastermind", int rank_ = 1, const std::vector<std::string>& intel_ = {"plan"})
        : Criminal(id_, std::move(name_), rank_, intel_) {}
    ~Mastermind() override = default;

    [[nodiscard]] double calculateThreatLevel() const override {
        double base = Criminal::calculateThreatLevel();
        double bonus = 0.0;
        for (const auto &s : getIntel()) if (s.find("plan") != std::string::npos) bonus += 6.0;
        return base + bonus;
    }

    [[nodiscard]] std::string specialty() const override { return "Mastermind"; }
    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override { return std::make_unique<Mastermind>(*this); }
    [[nodiscard]] std::string type() const override { return "Mastermind"; }
    [[nodiscard]] std::string summary() const override { return std::string("Mastermind: " + getName() + " (Rank: " + std::to_string(getRank()) + ")"); }
};

#endif // MASTERMIND_H

