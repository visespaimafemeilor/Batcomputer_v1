#pragma once
#include "exceptions.h"
#include "family.h"
#include "database_entry.h"
#include "criminals/criminals.h"
#include "criminals/hacker.h"
#include "batsuit.h"

class BatFactory {
public:
    static std::shared_ptr<DatabaseEntry> createEntry(const int typeId) {
        switch (typeId) {
        case 0: return std::make_shared<Criminal>();
        case 2: return std::make_shared<Hacker>();
        case 100: return std::make_shared<Family>();
        case 200: return std::make_shared<Batsuit>();
        default: throw DatabaseOperationException("Unknown Type ID for Factory");
        }
    }
};

