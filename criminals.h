//criminals.h
#ifndef CRIMINAL_H
#define CRIMINAL_H

#include "database_entry.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <random>

class Criminal : public DatabaseEntry{
private:
    int id;
    //std::string name;
    int rank;
    std::vector<std::string> intel;

public:
    explicit Criminal(int id_ = 1, std::string  name_ = "cr", int rank_ = 1, const std::vector<std::string>& intel_ = {"intel 1"});

    void displayInfo() const override
    {
        std::cout<<"--CRIMINAL FILE: "<<name<<"--\n";
        std::cout<<"Rank: "<<rank<<"\n";
    }

    double assessThreat() const override;
    std::unique_ptr<DatabaseEntry> clone() const override;

    // DatabaseEntry interface
    std::string type() const override;
    std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;

    Criminal(const Criminal& other);
    Criminal& operator=(Criminal other);
    friend void swap(Criminal& a, Criminal& b) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Criminal& cr);

    [[nodiscard]] int getId() const;
    //[[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getRank() const;
    [[nodiscard]] const std::vector<std::string>& getIntel() const;

    bool loadCriminal(std::istream& file);
    void promote(int inc=1);
    [[nodiscard]]double calculateThreatLevel() const;
    [[nodiscard]]bool simulateEscape(double facilitySecurityLevel) const;
};

#endif
