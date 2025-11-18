#ifndef FAMILY_H
#define FAMILY_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <sstream>
#include <random>
#include "criminals.h"

class Family
{
private:
    std::string codename;
    std::string civilian_name;
    int physical_power;
    std::vector<std::string> skills;

public:
    explicit Family(std::string  codename_ = "mem", std::string  civilian_name_ = "mem", int physical_power_ = 1, const std::vector<std::string>& skills_ = {"skill"});
    Family(const Family& other);
    Family& operator=(const Family& other);
    ~Family();

    friend std::ostream& operator<<(std::ostream& os, const Family& f);

    [[nodiscard]] const std::string& getCodename() const;
    [[nodiscard]] const std::string& getCivilianName() const;
    [[nodiscard]] int getPhysicalPower() const;
    [[nodiscard]] const std::vector<std::string>& getSkills() const;

    bool loadFamilyMember(std::istream& file);
    [[nodiscard]] bool fight(const Criminal& enemy) const;
    [[nodiscard]] std::string fightReport(const Criminal& enemy) const;
    [[nodiscard]] std::string simulateBattle(const Criminal& enemy) const;
};

#endif