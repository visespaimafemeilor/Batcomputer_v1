//family.h
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
#include "database_entry.h"

class Family : public DatabaseEntry{
private:
    //std::string codename;
    std::string civilian_name;
    int physical_power;
    std::vector<std::string> skills;

public:
    static int familyMemberCount;

    explicit Family(std::string  codename_ = "mem", std::string  civilian_name_ = "mem", int physical_power_ = 1, const std::vector<std::string>& skills_ = {"skill"});
    ~Family() override;

    void displayInfo() const override
    {
        std::cout << "--BAT-FAMILY MEMBER: "<<name<<" ("<<civilian_name<<")--\n";
    }

    double assessThreat() const override;
    std::unique_ptr<DatabaseEntry> clone() const override;

    // DatabaseEntry interface
    std::string type() const override;
    std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;

    Family(const Family& other);
    Family& operator=(Family other);
    friend void swap(Family& a, Family& b) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Family& f);

    [[nodiscard]] const std::string& getCodename() const;
    [[nodiscard]] const std::string& getCivilianName() const;
    [[nodiscard]] int getPhysicalPower() const;
    [[nodiscard]] const std::vector<std::string>& getSkills() const;

    static int getFamilyMemberCount() { return familyMemberCount; }

    bool loadFamilyMember(std::istream& file);
    [[nodiscard]] bool fight(const Criminal& enemy) const;
    [[nodiscard]] std::string fightReport(const Criminal& enemy) const;
    [[nodiscard]] std::string simulateBattle(const Criminal& enemy) const;
};

#endif
