#include "registrations.h"
#include "entry_factory.h"
#include "criminals/hacker.h"
#include "criminals/bank_robber.h"
#include "criminals/metahuman.h"
#include "criminals/crimeLord.h"
#include "criminals/criminals.h"
#include "batsuit.h"
#include "family.h"

void registerAllEntities() {
    static bool already_registered = false;
    if (already_registered) return;
    already_registered = true;

    // Register criminal types
    EntryFactory::registerFactory(static_cast<int>(CriminalType::HACKER), [] { return std::make_shared<Hacker>(); });
    EntryFactory::registerFactory(static_cast<int>(CriminalType::BANK_ROBBER), [] { return std::make_shared<BankRobber>(); });
    EntryFactory::registerFactory(static_cast<int>(CriminalType::METAHUMAN), [] { return std::make_shared<MetaHuman>(); });
    EntryFactory::registerFactory(static_cast<int>(CriminalType::CRIME_LORD), [] { return std::make_shared<CrimeLord>(); });
    EntryFactory::registerFactory(static_cast<int>(CriminalType::GENERIC), [] { return std::make_shared<Criminal>(); });

    // Register family and batsuit
    EntryFactory::registerFactory(100, [] { return std::make_shared<Family>(); });
    EntryFactory::registerFactory(200, [] { return std::make_shared<Batsuit>(); });
}
