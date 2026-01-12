#pragma once
#include "include/exceptions.h"
#include "include/family.h"
#include "include/database_entry.h"
#include "include/criminals/criminals.h"
#include "include/criminals/hacker.h"
#include "include/batsuit.h"

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