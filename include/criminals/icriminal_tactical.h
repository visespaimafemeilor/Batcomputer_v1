#ifndef ICRIMINAL_TACTICAL_H
#define ICRIMINAL_TACTICAL_H

#include "../database_entry.h"
#include <vector>
#include <memory>

class ITacticalSimulator {
public:
    virtual ~ITacticalSimulator() = default;

    virtual void onGlobalTacticalSimulation(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const = 0;
};

#endif // ICRIMINAL_TACTICAL_H

