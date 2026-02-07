#ifndef HACKER_H
#define HACKER_H

#include "criminals.h"
#include <vector>
#include <memory>

class Hacker final : public Criminal {
protected:
    int bypassLevel;
    void doDisplay(std::ostream& os) const override; //

public:
    explicit Hacker(int id_ = 0, const std::string& name_ = "", int rank_ = 1, int bypass_ = 5);

    [[nodiscard]] std::unique_ptr<DatabaseEntry> clone() const override; //

    void hackSystem(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const;

    [[nodiscard]] double calculateThreatLevel() const override;
    [[nodiscard]] std::string type() const override;
    void save(std::ostream& out) const override;

    Hacker* asHacker() override { return this; }
    [[nodiscard]] const Hacker* asHacker() const override { return this; }
};

#endif