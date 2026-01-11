#ifndef METAHUMAN_H
#define METAHUMAN_H

#include "criminals.h"

class MetaHuman : public Criminal {
private:
    std::string powerSource;
    double powerScale;

public:
    MetaHuman(int id_ = 0, std::string name_ = "", int rank_ = 1, 
              std::string source = "Unknown", double scale = 1.0)
        : Criminal(id_, name_, rank_, {}, CriminalType::METAHUMAN), 
          powerSource(source), powerScale(scale) {}

    double calculateThreatLevel() const override {
        return (Criminal::calculateThreatLevel() * powerScale) + 50.0;
    }

    std::string type() const override { return "Meta-Human"; }

    std::string specialty() const override {
        return "Superhuman Ability: " + powerSource;
    }

    void save(std::ostream& out) const override {
        Criminal::save(out); // Salvăm datele de bază
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