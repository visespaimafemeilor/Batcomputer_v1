#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <vector>
#include <memory>
#include "../database_entry.h"

class EntityFactory {
public:
    explicit EntityFactory(std::vector<std::shared_ptr<DatabaseEntry>>& db);

    void addNewCriminal() const;
    void addNewFamilyMember() const;
    void addNewBatsuitPart() const;

private:
    std::vector<std::shared_ptr<DatabaseEntry>>& database;
};

#endif