#ifndef ICRIMINAL_CYBER_H
#define ICRIMINAL_CYBER_H

#include "../database_entry.h"
#include <vector>
#include <memory>

class ICyberThreat {
public:
    virtual ~ICyberThreat() = default;

    [[nodiscard]] virtual int hackerCountContribution() const = 0;

    virtual void onCyberSweep(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const = 0;

    virtual void runForensicsAction(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const = 0;
};

#endif // ICRIMINAL_CYBER_H

