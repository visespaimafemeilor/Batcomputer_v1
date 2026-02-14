#include "entry_factory.h"
#include "database_entry.h"

#include <mutex>

using Creator = EntryFactory::Creator;

std::unordered_map<int, Creator>& EntryFactory::registry() {
    static std::unordered_map<int, Creator> instance;
    return instance;
}

bool EntryFactory::registerFactory(const int typeId, Creator creator) {
    auto& reg = registry();
    // If already present, don't overwrite
    if (reg.contains(typeId)) return false;
    reg[typeId] = std::move(creator);
    return true;
}

std::shared_ptr<DatabaseEntry> EntryFactory::create(const int typeId) {
    auto& reg = registry();
    const auto it = reg.find(typeId);
    if (it == reg.end()) return nullptr;
    return it->second();
}

