#ifndef BANK_ROBBER_H
#define BANK_ROBBER_H

#include "criminals.h"

class BankRobber : public Criminal {
private:
    int successfulHeists;
    bool hasGetawayVehicle;

public:
    BankRobber(int id_ = 0, std::string name_ = "", int rank_ = 1,
               int heists = 0, bool vehicle = false)
        : Criminal(id_, name_, rank_, {}, CriminalType::BANK_ROBBER),
          successfulHeists(heists), hasGetawayVehicle(vehicle) {}

    double calculateThreatLevel() const override {
        double base = Criminal::calculateThreatLevel();
        if (hasGetawayVehicle) base += 15.0; // Mai greu de prins
        return base + (successfulHeists * 2);
    }

    std::string type() const override { return "Bank Robber"; }

    std::string specialty() const override {
        return "Expert in Heists. Success rate: " + std::to_string(successfulHeists);
    }

    void save(std::ostream& out) const override {
        Criminal::save(out);
        out << successfulHeists << "\n";
        out << (hasGetawayVehicle ? 1 : 0) << "\n";
    }

    bool load(std::istream& in) override {
        if (!Criminal::load(in)) return false;
        int vehicleInt;
        in >> successfulHeists >> vehicleInt;
        hasGetawayVehicle = (vehicleInt == 1);
        return true;
    }
};

#endif