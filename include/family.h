#ifndef FAMILY_H
#define FAMILY_H

#include "database_entry.h"
#include <string>
#include <vector>
#include <iostream>
#include "criminals/criminals.h"

class Family : public DatabaseEntry {
protected:
    std::string civilian_name;
    int physical_power;
    std::vector<std::string> skills;
public:
    static int familyMemberCount;

    explicit Family(std::string codename_ = "", std::string civilian_name_ = "", int physical_power_ = 0, const std::vector<std::string>& skills_ = {})
        : DatabaseEntry(std::move(codename_)), civilian_name(std::move(civilian_name_)), physical_power(physical_power_), skills(skills_) { ++familyMemberCount; }
    ~Family() override;

    // copy constructor
    Family(const Family& other);

    friend void swap(Family& a, Family& b) noexcept;
    Family& operator=(Family other);

    std::unique_ptr<DatabaseEntry> clone() const override;

    // DatabaseEntry implementations
    void displayInfo() const override;
    double assessThreat() const override;
    std::string type() const override;
    std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;
    static void showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db);

    // getters
    [[nodiscard]] const std::string& getCodename() const;
    [[nodiscard]] const std::string& getCivilianName() const;
    [[nodiscard]] int getPhysicalPower() const;
    [[nodiscard]] const std::vector<std::string>& getSkills() const;

    static int getFamilyMemberCount() { return familyMemberCount; }

    bool loadFamilyMember(std::istream& file);

    [[nodiscard]] bool fight(const Criminal& enemy) const;
    [[nodiscard]] std::string fightReport(const Criminal& enemy) const;
    [[nodiscard]] std::string simulateBattle(const Criminal& enemy) const;

    // interactions with other database entries
    std::string interact(DatabaseEntry& other) override;
    static void coordinateRepairs(const std::vector<std::shared_ptr<DatabaseEntry>>& database);
    static void simulateSiege(const std::vector<std::shared_ptr<DatabaseEntry>>& database);
    static void runTrainingDay(std::vector<std::shared_ptr<DatabaseEntry>>& database, const std::string& memberName);
};

#endif // FAMILY_H

