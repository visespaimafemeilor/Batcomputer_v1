#ifndef BANK_ROBBER_H
#define BANK_ROBBER_H

#include "criminals.h"

class BankRobber : public Criminal {
public:
    explicit BankRobber(int id_ = 1, std::string name_ = "bankrob", int rank_ = 1, const std::vector<std::string>& intel_ = {"vault"})
        : Criminal(id_, std::move(name_), rank_, intel_) {}
    ~BankRobber() override = default;

    [[nodiscard]] double calculateThreatLevel() const override {
        double base = Criminal::calculateThreatLevel();
        double bonus = 0.0;
        for (const auto &s : getIntel()) if (s.find("vault") != std::string::npos) bonus += 5.0;
        return base + bonus;
    }

    [[nodiscard]] std::string specialty() const override { return "BankRobber"; }

    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override { return std::make_unique<BankRobber>(*this); }

    [[nodiscard]] std::string type() const override { return "BankRobber"; }
    [[nodiscard]] std::string summary() const override { return "BankRobber: " + getName() + " (Rank: " + std::to_string(getRank()) + ")"; }
};

#endif // BANK_ROBBER_H

