#ifndef IBATSUIT_H
#define IBATSUIT_H

#include "database_entry.h"
#include <memory>
#include <string>

class IBatsuit : public DatabaseEntry {
public:
    explicit IBatsuit(const std::string& n = "") : DatabaseEntry(n) {}
    ~IBatsuit() override = default;

    virtual void applyDamage(int dmg) = 0;
    virtual std::string modeName() const = 0;
    virtual double integrity() const = 0;
    virtual std::unique_ptr<DatabaseEntry> clone() const = 0;
};

#endif // IBATSUIT_H

