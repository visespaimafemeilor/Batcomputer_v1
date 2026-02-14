#include "criminals/bank_robber.h"
#include "entry_factory.h"

BankRobber::BankRobber(const int id_, const std::string& name_, const int rank_, const int heists, const bool vehicle)
    : Criminal(id_, name_, rank_, {}, CriminalType::BANK_ROBBER),
      successfulHeists(heists), hasGetawayVehicle(vehicle) {}

std::unique_ptr<DatabaseEntry> BankRobber::clone() const {
    return std::make_unique<BankRobber>(*this);
}

void BankRobber::doDisplay(std::ostream& os) const {
    Criminal::doDisplay(os);
    os << " | Success Heists: " << successfulHeists
       << " | Getaway Vehicle: " << (hasGetawayVehicle ? "Yes" : "No") << "\n";
}

double BankRobber::calculateThreatLevel() const {
    double base = Criminal::calculateThreatLevel();
    if (hasGetawayVehicle) base += 15.0;
    return base + successfulHeists * 2;
}

std::string BankRobber::type() const { return "Bank Robber"; }

std::string BankRobber::specialty() const {
    return "Expert in Heists. Success rate: " + std::to_string(successfulHeists);
}

void BankRobber::save(std::ostream& out) const {
    Criminal::save(out);
    out << successfulHeists << "\n" << (hasGetawayVehicle ? 1 : 0) << "\n";
}

bool BankRobber::load(std::istream& in) {
    if (!Criminal::load(in)) return false;
    int vehicleInt;
    in >> successfulHeists >> vehicleInt;
    hasGetawayVehicle = vehicleInt == 1;
    return true;
}
