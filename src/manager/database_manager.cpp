#include "manager/database_manager.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>
#include <utility>

DatabaseManager::DatabaseManager(std::vector<std::shared_ptr<DatabaseEntry>>& db, std::string  filename)
    : database(db), dbFilename(std::move(filename)) {}

void DatabaseManager::load() const
{
    std::ifstream fin(dbFilename);
    if (!fin) {
        throw FileLoadException(dbFilename);
    }

    int total;
    if (!(fin >> total)) return;

    database.clear();
    for (int i = 0; i < total; ++i) {
        if (auto obj = DatabaseEntry::createFromStream(fin)) {
            database.push_back(obj);
        }
    }
    std::cout << "[SYSTEM] Loaded " << database.size() << " entities.\n";
}

void DatabaseManager::save() const {
    std::ofstream fout(dbFilename);
    if (!fout) {
        throw DatabaseOperationException("Could not open file for saving.");
    }

    fout << database.size() << "\n";
    for (const auto& entry : database) {
        entry->save(fout);
    }
    std::cout << "[SYSTEM] Progress saved to " << dbFilename << ".\n";
}
