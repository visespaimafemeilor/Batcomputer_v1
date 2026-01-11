#ifndef CRIMINALS_H
#define CRIMINALS_H

#include "../database_entry.h"
#include <string>
#include <vector>
#include <iostream>

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
public:
    static int criminalCount;

    explicit Criminal(int id_ = 0, std::string name_ = "", int rank_ = 1, const std::vector<std::string>& intel_ = {}, CriminalType cat = CriminalType::GENERIC);
    ~Criminal() override;

    friend std::ostream& operator<<(std::ostream& os, const Criminal& cr);

    int getId() const;
    int getRank() const;
    const std::vector<std::string>& getIntel() const;

    static int getCriminalCount() { return criminalCount; }

    bool loadCriminal(std::istream& file);
    void promote(int inc = 1);
    virtual double calculateThreatLevel() const;
    void displayInfo() const override;

    double assessThreat() const override;
    std::unique_ptr<DatabaseEntry> clone() const override;

    Criminal(const Criminal& other);
    Criminal& operator=(Criminal other);
    friend void swap(Criminal& a, Criminal& b) noexcept;

    std::string type() const override;
    std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;

    bool simulateEscape(double facilitySecurityLevel) const;

    virtual std::string specialty() const { return std::string(); }

    std::string interact(DatabaseEntry& other) override;

    static void simulateArkhamBlackout(std::vector<std::shared_ptr<DatabaseEntry>>& database, double systemSecurity);

    static void generateStrategicReport(const std::vector<std::shared_ptr<DatabaseEntry>>& database);

};

#endif // CRIMINALS_H

