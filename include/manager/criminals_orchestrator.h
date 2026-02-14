#ifndef CRIMINALS_ORCHESTRATOR_H
#define CRIMINALS_ORCHESTRATOR_H

#include "../database_entry.h"
#include <vector>
#include <memory>

namespace manager {

void simulateArkhamBlackout(std::vector<std::shared_ptr<DatabaseEntry>>& database, double systemSecurity);

void generateStrategicReport(const std::vector<std::shared_ptr<DatabaseEntry>>& database);

void runForensics(const std::vector<std::shared_ptr<DatabaseEntry>>& database);

}

#endif // CRIMINALS_ORCHESTRATOR_H

