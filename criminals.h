#ifndef CRIMINAL_H
#define CRIMINAL_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <random>

class Criminal{
private:
    int id;
    std::string name;
    int rank;
    std::vector<std::string> intel;

public:
    explicit Criminal(int id_ = 1, std::string  name_ = "cr", int rank_ = 1, const std::vector<std::string>& intel_ = {"intel 1"});
    Criminal(const Criminal& other) = default;
    Criminal& operator=(const Criminal& other) = default;
    ~Criminal() = default;

    friend std::ostream& operator<<(std::ostream& os, const Criminal& cr);

    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getRank() const;
    [[nodiscard]] const std::vector<std::string>& getIntel() const;

    bool loadCriminal(std::istream& file);
    void promote(int inc=1);
    [[nodiscard]]double calculateThreatLevel() const;
    [[nodiscard]]bool simulateEscape(double facilitySecurityLevel) const;
};

#endif