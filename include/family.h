#ifndef FAMILY_H
#define FAMILY_H

#include "database_entry.h"
#include <string>
#include <vector>

class Family final : public DatabaseEntry {
protected:
    std::string civilian_name;
    int physical_power;
    std::vector<std::string> skills;
    void doDisplay(std::ostream& os) const override;
public:
    static int familyMemberCount;

    explicit Family(std::string codename_ = "", std::string civilian_name_ = "", const int physical_power_ = 0, const std::vector<std::string>& skills_ = {})
        : DatabaseEntry(std::move(codename_)), civilian_name(std::move(civilian_name_)), physical_power(physical_power_), skills(skills_) { ++familyMemberCount; }
    ~Family() override;

    Family(const Family& other);

    friend void swap(Family& a, Family& b) noexcept;
    Family& operator=(Family other);

    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override;

    [[nodiscard]] double assessThreat() const override;
    [[nodiscard]] std::string type() const override;
    [[nodiscard]] std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;
    static void showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db);

    [[nodiscard]] const std::string& getCodename() const;
    [[nodiscard]] int getPhysicalPower() const;

    bool loadFamilyMember(std::istream& file);

    [[nodiscard]] bool fight(const Criminal& enemy) const;
    [[nodiscard]] std::string fightReport(const Criminal& enemy) const;
    [[nodiscard]] std::string simulateBattle(const Criminal& enemy) const;

    std::string interact(DatabaseEntry& other) override;

    std::string interactedBy(const Criminal& c) override;
    std::string interactedBy(const Batsuit& b) override;

    Family* asFamily() override { return this; }
    [[nodiscard]] const Family* asFamily() const override { return this; }

    static void coordinateRepairs(const std::vector<std::shared_ptr<DatabaseEntry>>& database);
    static void simulateSiege(const std::vector<std::shared_ptr<DatabaseEntry>>& database);
    static void runTrainingDay(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const std::string& memberName);
};

#endif // FAMILY_H

