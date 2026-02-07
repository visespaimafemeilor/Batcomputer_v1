#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "../database_entry.h"

class DatabaseManager {
public:
    DatabaseManager(std::vector<std::shared_ptr<DatabaseEntry>>& db, std::string  filename);
    void load() const;
    void save() const;

private:
    std::vector<std::shared_ptr<DatabaseEntry>>& database;
    std::string dbFilename;
};

#endif

