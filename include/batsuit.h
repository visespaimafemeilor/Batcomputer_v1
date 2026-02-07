//batsuit.h
#ifndef BATSUIT_H
#define BATSUIT_H

#include "database_entry.h"
#include <string>
#include <vector>

class Batsuit final : public DatabaseEntry{
protected:
    int level;
    double integrity;

    void normalize();
    void doDisplay(std::ostream& os) const override;

public:
    static int suitPartCount;

    explicit Batsuit(int level_ = 1, std::string  part_ = "p", double integrity_ = 1.00);
    ~Batsuit() override;

    [[nodiscard]] double assessThreat() const override;
    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override;

    [[nodiscard]] std::string type() const override;
    [[nodiscard]] std::string summary() const override;
    bool load(std::istream& in) override;
    void save(std::ostream& out) const override;
    static void showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db);

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
    void applyBattleDamage(double damageBad);

    std::string interact(DatabaseEntry& other) override;

    std::string interactedBy(const Criminal& c) override;
    std::string interactedBy(const Family& f) override;

    Batsuit* asBatsuit() override { return this; }
    [[nodiscard]] const Batsuit* asBatsuit() const override { return this; }

    static void redistributeIntegrity(const std::vector<std::shared_ptr<DatabaseEntry>>& database);
    static void calculateSurvivalOdds(const std::vector<std::shared_ptr<DatabaseEntry>>& database, const std::string& enemyName);
};

#endif

