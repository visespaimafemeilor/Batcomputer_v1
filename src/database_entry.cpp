#include "database_entry.h"
#include "../include/criminals/criminals.h"
#include "family.h"
#include "batsuit.h"
#include "../include/criminals/hacker.h"
#include "../include/criminals/bank_robber.h"
#include "../include/criminals/metahuman.h"
#include "../include/criminals/crimeLord.h"
#include <limits>
#include <iostream>


int DatabaseEntry::totalEntities = 0;

std::shared_ptr<DatabaseEntry> DatabaseEntry::createFromStream(std::istream& in) {
    int typeId;

    if (!(in >> typeId)) {
        return nullptr;
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
        // daca nu este 100 sau 200, presupunem ca este un cod de Criminal
        CriminalType ct = static_cast<CriminalType>(typeId);

        switch (ct) {
            case CriminalType::HACKER:
                entry = std::make_shared<Hacker>();
                break;
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