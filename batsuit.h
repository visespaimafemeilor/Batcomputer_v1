//batsuit.h
#ifndef BATSUIT_H
#define BATSUIT_H

#include "batman.h"
#include <iostream>
#include <string>
#include <utility>
#include <limits>

class Batsuit : public Batman{
private:
    int level;
    //std::string part;
    double integrity;

    void normalize();

public:
    explicit Batsuit(int level_ = 1, std::string  part_ = "p", double integrity_ = 1.00);

    void displayInfo() const override
    {
        std::cout<<"-- SUIT COMPONENT: "<< name<<" (Integrity: "<<integrity<<"%) --\n";
    }

    //Batsuit(const Batsuit& other) = default;
    //Batsuit& operator= (const Batsuit& other) = default;
    //~Batsuit() = default;

    friend std::ostream& operator<<(std::ostream& os, const Batsuit& bs);

    [[nodiscard]] int getLevel() const;
    [[nodiscard]] const std::string& getPart() const;
    [[nodiscard]] double getIntegrity() const;

    bool loadBatsuit(std::istream& file);
    [[nodiscard]] bool isCritical(double muchie=30.0) const;
    [[nodiscard]] std::string statusReport() const;
    void applyBattleDamage(int damageBad);
};

#endif
