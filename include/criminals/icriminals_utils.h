#ifndef ICRIMINALS_UTILS_H
#define ICRIMINALS_UTILS_H

#include "../database_entry.h"
#include <memory>


template <typename Interface>

const Interface* asInterface(const std::shared_ptr<DatabaseEntry>& e) {
    if (!e) return nullptr;
    if (const Criminal* c = e->asCriminal()) {
        return dynamic_cast<const Interface*>(c);
    }
    return nullptr;
}

#endif // ICRIMINALS_UTILS_H

