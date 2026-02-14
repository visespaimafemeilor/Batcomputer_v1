#ifndef METAHUMAN_H
#define METAHUMAN_H

#include "criminals.h"
#include <vector>
#include <memory>
#include "icriminal_tactical.h"
#include "icriminal_specialist.h"

class MetaHuman final : public Criminal, public ITacticalSimulator, public ISpecialist {
protected:
    std::string powerSource;
    double powerScale;

    void doDisplay(std::ostream& os) const override;

public:
    explicit MetaHuman(int id_ = 0, const std::string& name_ = "", int rank_ = 1,
              std::string source = "Unknown", double scale = 1.0);

    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override;

    [[nodiscard]] double calculateThreatLevel() const override;
    [[nodiscard]] std::string type() const override;
    [[nodiscard]] std::string specialty() const override;

    void save(std::ostream& out) const override;
    bool load(std::istream& in) override;

    void onGlobalTacticalSimulation(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const override;
};

#endif