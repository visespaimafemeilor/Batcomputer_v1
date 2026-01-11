#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>
#include <memory>
#include <iostream>

class DatabaseEntry {
protected:
    std::string name;
public:
    static int totalEntities;

    explicit DatabaseEntry(std::string n = "") : name(std::move(n)) { ++totalEntities; }
    virtual ~DatabaseEntry() { --totalEntities; }

    // common accessor used throughout the project
    [[nodiscard]] const std::string& getName() const { return name; }

    // lightweight domain hooks that existing classes implement
    virtual void displayInfo() const = 0;
    virtual double assessThreat() const = 0;

    // polymorphic I/O and summary
    virtual std::string type() const { return std::string("DatabaseEntry"); }
    virtual std::string summary() const { return name; }
    virtual bool load(std::istream& in) { (void)in; return false; }
    virtual void save(std::ostream& out) const { out << name << "\n"; }


    virtual std::string interact(DatabaseEntry& other) { (void)other; return std::string("No interaction available"); }

    // virtual copy
    virtual std::unique_ptr<DatabaseEntry> clone() const = 0;

    static int getTotalEntities() { return totalEntities; }

    static std::shared_ptr<DatabaseEntry> createFromStream(std::istream& in);
};

#endif // DATABASE_ENTRY_H

