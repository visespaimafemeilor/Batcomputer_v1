#ifndef STEALTH_SUIT_H
#define STEALTH_SUIT_H

#include "ibatsuit.h"
#include "batsuit.h"
#include <vector>

class StealthSuit : public IBatsuit {
private:
    std::vector<Batsuit> parts;
    double cachedIntegrity = 100.0;
public:
    explicit StealthSuit(std::vector<Batsuit> p)
        : IBatsuit(std::string("StealthSuit")), parts(std::move(p)) {
        // compute aggregated integrity
        if(!parts.empty()){
            double sum = 0.0;
            for(const auto &pt : parts) sum += pt.getIntegrity();
            cachedIntegrity = sum / parts.size();
        }
    }
    ~StealthSuit() override = default;

    void applyDamage(int dmg) override {
        // distribute damage across parts
        if(parts.empty()) return;
        double per = static_cast<double>(dmg) / parts.size();
        for(auto &pt : parts){
            pt.applyBattleDamage(static_cast<int>(per));
        }
        // recompute integrity
        double sum = 0.0;
        for(const auto &pt : parts) sum += pt.getIntegrity();
        cachedIntegrity = sum / parts.size();
    }

    std::string modeName() const override { return std::string("Stealth"); }
    double integrity() const override { return cachedIntegrity; }

    // DatabaseEntry overrides to satisfy abstract requirements
    void displayInfo() const override {
        std::cout << "-- STEALTH SUIT: " << name << " (Integrity: " << cachedIntegrity << "%) --\n";
    }

    double assessThreat() const override {
        // threat inversely proportional to integrity (example heuristic)
        return (100.0 - cachedIntegrity) * 0.1;
    }

    std::string type() const override { return std::string("StealthSuit"); }
    std::string summary() const override { return "StealthSuit (Integrity: " + std::to_string(cachedIntegrity) + ")"; }

    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override { return std::make_unique<StealthSuit>(*this); }
};

#endif // STEALTH_SUIT_H

