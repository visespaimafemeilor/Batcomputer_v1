#ifndef METAHUMAN_H
#define METAHUMAN_H

#include <utility>

#include "criminals.h"

class MetaHuman : public Criminal {
private:
    std::string powerSource;
    double powerScale;

public:
    explicit MetaHuman(const int id_ = 0, const std::string& name_ = "", const int rank_ = 1,
              std::string  source = "Unknown", const double scale = 1.0)
        : Criminal(id_, name_, rank_, {}, CriminalType::METAHUMAN), 
          powerSource(std::move(source)), powerScale(scale) {}

    [[nodiscard]] double calculateThreatLevel() const override {
        return (Criminal::calculateThreatLevel() * powerScale) + 50.0;
    }

    [[nodiscard]] std::string type() const override { return "Meta-Human"; }

    [[nodiscard]] std::string specialty() const override {
        return "Superhuman Ability: " + powerSource;
    }

    void save(std::ostream& out) const override {
        Criminal::save(out);
        out << powerSource << "\n";
        out << powerScale << "\n";
    }

    bool load(std::istream& in) override {
        if (!Criminal::load(in)) return false;
        in >> powerSource >> powerScale;
        return true;
    }
};

#endif