#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>
#include <memory>
#include <iostream>

class Family;
class Criminal;
class Batsuit;
class CrimeLord;
class Hacker;
class BankRobber;
class MetaHuman;

class DatabaseEntry {
protected:
    std::string name;
    virtual void doDisplay(std::ostream& os) const = 0;
public:
    static int totalEntities;

    explicit DatabaseEntry(std::string n = "") : name(std::move(n)) { ++totalEntities; }
    virtual ~DatabaseEntry() { --totalEntities; }

    [[nodiscard]] const std::string& getName() const { return name; }

    void displayInfo() const {
        doDisplay(std::cout);
    }
    [[nodiscard]] virtual double assessThreat() const = 0;

    [[nodiscard]] virtual std::string type() const { return "DatabaseEntry"; }
    [[nodiscard]] virtual std::string summary() const { return name; }
    virtual bool load(std::istream& in) { (void)in; return false; }
    virtual void save(std::ostream& out) const { out << name << "\n"; }


    virtual std::string interact(DatabaseEntry& other) {
        (void)other;
        return {"No interaction available"};
    }

    virtual std::string interactedBy(const Family& f) { (void)f; return {}; }
    virtual std::string interactedBy(const Criminal& c) { (void)c; return {}; }
    virtual std::string interactedBy(const Batsuit& b) { (void)b; return {}; }

    virtual Family* asFamily() { return nullptr; }
    [[nodiscard]] virtual const Family* asFamily() const { return nullptr; }

    virtual Criminal* asCriminal() { return nullptr; }
    [[nodiscard]] virtual const Criminal* asCriminal() const { return nullptr; }

    virtual Batsuit* asBatsuit() { return nullptr; }
    [[nodiscard]] virtual const Batsuit* asBatsuit() const { return nullptr; }

    virtual CrimeLord* asCrimeLord() { return nullptr; }
    [[nodiscard]] virtual const CrimeLord* asCrimeLord() const { return nullptr; }

    virtual Hacker* asHacker() { return nullptr; }
    [[nodiscard]] virtual const Hacker* asHacker() const { return nullptr; }

    virtual BankRobber* asBankRobber() { return nullptr; }
    [[nodiscard]] virtual const BankRobber* asBankRobber() const { return nullptr; }

    virtual MetaHuman* asMetaHuman() { return nullptr; }
    [[nodiscard]] virtual const MetaHuman* asMetaHuman() const { return nullptr; }

    [[nodiscard]] virtual std::unique_ptr<DatabaseEntry> clone() const = 0;

    static std::shared_ptr<DatabaseEntry> createFromStream(std::istream& in);

    template <typename T1, typename T2>
    static bool compareEfficiency(const T1& a, const T2& b) {
        return a.assessThreat() > b.assessThreat();
    }
};

template <typename T1, typename T2>
bool compareEfficiency(const T1& a, const T2& b) {
    return a.assessThreat() > b.assessThreat();
}

#endif // DATABASE_ENTRY_H

