#include "database_entry.h"
#include "criminals/criminals.h"
#include "family.h"
#include "batsuit.h"
#include "criminals/hacker.h"
#include "criminals/bank_robber.h"
#include "criminals/metahuman.h"
#include "criminals/crimeLord.h"
#include "entry_factory.h"
#include <limits>
#include <iostream>


int DatabaseEntry::totalEntities = 0;

std::shared_ptr<DatabaseEntry> DatabaseEntry::createFromStream(std::istream& in) {
    int typeId;

    if (!(in >> typeId)) {
        return nullptr;
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (auto entry = EntryFactory::create(typeId)) {
        if (entry->load(in)) return entry;
        return nullptr;
    }

    std::shared_ptr<DatabaseEntry> entry = nullptr;

    // Logica de selectie:
    // 100 = Family Member
    // 200 = Batsuit Part
    // 0-4 = Criminal Types (bazat pe CriminalType enum)

    if (typeId == 100) {
        entry = std::make_shared<Family>();
    }
    else if (typeId == 200) {
        entry = std::make_shared<Batsuit>();
    }
    else {
        // if not 100 or 200, assume it's a criminal code
        switch (static_cast<CriminalType>(typeId)) {
        // daca nu este 100 sau 200, presupunem ca este un cod de Criminal

//                entry = std::make_shared<Hacker>();
//                break;
            case CriminalType::BANK_ROBBER:
                entry = std::make_shared<BankRobber>();
                break;
            case CriminalType::METAHUMAN:
                entry = std::make_shared<MetaHuman>();
                break;
            case CriminalType::CRIME_LORD:
                entry = std::make_shared<CrimeLord>();
                break;
            default:
                entry = std::make_shared<Criminal>();
                break;
        }
    }

    if (entry && entry->load(in)) {
        return entry;
    }

    return nullptr;
}