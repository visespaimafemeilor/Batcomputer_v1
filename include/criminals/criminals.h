#ifndef CRIMINALS_H
#define CRIMINALS_H

#include "../database_entry.h"
#include <string>
#include <vector>

enum class CriminalType {
    GENERIC,
    BANK_ROBBER,
    HACKER,
    CRIME_LORD,
    METAHUMAN
};

class Criminal : public DatabaseEntry {
protected:
    int id;
    int rank;
    std::vector<std::string> intel;
    CriminalType category;
    void doDisplay(std::ostream& os) const override;
public:
    static int criminalCount;

    explicit Criminal(int id_ = 0, std::string name_ = "", int rank_ = 1, const std::vector<std::string>& intel_ = {}, CriminalType cat = CriminalType::GENERIC);
    ~Criminal() override;

    friend std::ostream& operator<<(std::ostream& os, const Criminal& cr);

    [[nodiscard]] int getId() const;
    [[nodiscard]] int getRank() const;
    [[nodiscard]] const std::vector<std::string>& getIntel() const;

    //bool loadCriminal(std::istream& file);
    void promote(int inc = 1);
    [[nodiscard]] virtual double calculateThreatLevel() const;

    [[nodiscard]] double assessThreat() const override;
    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override;

    Criminal(const Criminal& other);
    Criminal& operator=(Criminal other);
    friend void swap(Criminal& a, Criminal& b) noexcept;

    [[nodiscard]] std::string type() const override;
    [[nodiscard]] std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;
    static void showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db);

    static void searchByName(const std::vector<std::shared_ptr<DatabaseEntry>>& db, const std::string& name);
    static void promoteByName(const std::vector<std::shared_ptr<DatabaseEntry>>& db, const std::string& name);

    [[nodiscard]] bool simulateEscape(double facilitySecurityLevel) const;

    [[nodiscard]] virtual std::string specialty() const { return {}; }

    std::string interact(DatabaseEntry& other) override;
    static void simulateArkhamBlackout(std::vector<std::shared_ptr<DatabaseEntry>>& database, double systemSecurity);
    static void generateStrategicReport(const std::vector<std::shared_ptr<DatabaseEntry>>& database);
    static void runForensics(const std::vector<std::shared_ptr<DatabaseEntry>>& database);

};

#endif // CRIMINALS_H

