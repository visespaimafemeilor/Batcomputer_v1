//batsuit.h
#ifndef BATSUIT_H
#define BATSUIT_H

#include "database_entry.h"
#include <iostream>
#include <string>
#include <utility>
#include <limits>

class Batsuit : public DatabaseEntry{
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

    double assessThreat() const override;
    std::unique_ptr<DatabaseEntry> clone() const override;

    // DatabaseEntry interface
    std::string type() const override;
    std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;

    Batsuit(const Batsuit& other);
    Batsuit& operator=(Batsuit other);
    friend void swap(Batsuit& a, Batsuit& b) noexcept;

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
