#ifndef ICRIMINAL_LEADER_H
#define ICRIMINAL_LEADER_H

#include "../database_entry.h"
#include <vector>
#include <memory>

class ILeaderInfluence {
public:
    virtual ~ILeaderInfluence() = default;

    [[nodiscard]] virtual int leaderInfluenceContribution() const = 0;

    virtual void onUnderworldSting(const std::vector<std::shared_ptr<DatabaseEntry>>& database) const = 0;

    virtual void affectBlackoutSecurity(double& systemSecurity) const = 0;
};

#endif // ICRIMINAL_LEADER_H
