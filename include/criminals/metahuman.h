#ifndef METAHUMAN_H
#define METAHUMAN_H

#include "criminals.h"

class MetaHuman final : public Criminal {
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

    MetaHuman* asMetaHuman() override { return this; }
    [[nodiscard]] const MetaHuman* asMetaHuman() const override { return this; }
};

#endif