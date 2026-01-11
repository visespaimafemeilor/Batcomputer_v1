#ifndef CRIME_LORD_H
#define CRIME_LORD_H

#include "criminals.h"
#include <vector>
#include <memory>

class CrimeLord final : public Criminal {
public:
    explicit CrimeLord(int id_ = 0, const std::string& name_ = "", int rank_ = 1);

    void inspireThugs(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const;

    [[nodiscard]] double calculateThreatLevel() const override;
    [[nodiscard]] std::string type() const override;
};

#endif