#ifndef BANK_ROBBER_H
#define BANK_ROBBER_H

#include "criminals.h"
#include "icriminal_specialist.h"

class BankRobber final : public Criminal, public ISpecialist {
protected:
    int successfulHeists;
    bool hasGetawayVehicle;

    void doDisplay(std::ostream& os) const override;

public:
    explicit BankRobber(int id_ = 0, const std::string& name_ = "", int rank_ = 1,
               int heists = 0, bool vehicle = false);

    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override;

    [[nodiscard]] double calculateThreatLevel() const override;
    [[nodiscard]] std::string type() const override;
    [[nodiscard]] std::string specialty() const override;

    void save(std::ostream& out) const override;
    bool load(std::istream& in) override;
};

#endif