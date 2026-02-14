#ifndef ENTRY_FACTORY_H
#define ENTRY_FACTORY_H

#include <functional>
#include <memory>
#include <unordered_map>

class DatabaseEntry;

class EntryFactory {
public:
    using Creator = std::function<std::shared_ptr<DatabaseEntry>()>;

    // Register a creator for a type id. Returns true if registration succeeded.
    static bool registerFactory(int typeId, Creator creator);

    // Create an instance for the given type id. Returns nullptr if not found.
    static std::shared_ptr<DatabaseEntry> create(int typeId);

private:
    static std::unordered_map<int, Creator>& registry();
};

#endif // ENTRY_FACTORY_H

