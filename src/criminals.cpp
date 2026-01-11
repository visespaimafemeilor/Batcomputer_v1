//criminals.cpp
#include "criminals.h"
#include "family.h"
#include "batsuit.h"
#include "hacker.h"
#include "crimeLord.h"
#include "bank_robber.h"
#include "metahuman.h"
#include <memory>
#include <utility>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

int Criminal::criminalCount = 0;


Criminal::Criminal(int id_, std::string name_, int rank_, const std::vector<std::string>& intel_, CriminalType cat) :
    DatabaseEntry(std::move(name_)),
    id{id_},
    rank{rank_},
    intel{intel_},
    category{cat}
{ ++criminalCount; }

Criminal::~Criminal() { --criminalCount; }


std::ostream& operator<<(std::ostream& os, const Criminal& cr)
{
    os<<"Id: "<<cr.id<< " Codename: "<<cr.name<<"\n";
    os<<"Rank: "<<cr.rank<<"\n";
    return os;
}

void Criminal::displayInfo() const {
    std::cout << "-- CRIMINAL: " << name << " (Rank: " << rank << ") --\n";
}

int Criminal::getId() const {return id;}
//const string& Criminal::getName() const  { return name; }
int Criminal::getRank() const  { return rank; }
const std::vector<std::string>& Criminal::getIntel() const  { return intel; }


std::unique_ptr<Criminal> CriminalFactory(std::istream& in) {
    int typeInt;
    if (!(in >> typeInt)) return nullptr;

    CriminalType type = static_cast<CriminalType>(typeInt);
    std::unique_ptr<Criminal> c;

    switch (type) {
        case CriminalType::HACKER:      c = std::make_unique<Hacker>(); break;
        case CriminalType::BANK_ROBBER: c = std::make_unique<BankRobber>(); break;
        case CriminalType::METAHUMAN:   c = std::make_unique<MetaHuman>(); break;
        case CriminalType::CRIME_LORD:  c = std::make_unique<CrimeLord>(); break;
        default:                        c = std::make_unique<Criminal>(); break;
    }

    if (c && c->load(in)) {
        return c;
    }
    return nullptr;
}
bool Criminal::load(std::istream& in) {
    // Folosim logica existentă de citire
    if(!(in >> id)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(!getline(in, name)) return false;
    if(!(in >> rank)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int intelCount;
    if(!(in >> intelCount)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    intel.clear();
    for(int i = 0; i < intelCount; ++i) {
        std::string line;
        if(!getline(in, line)) return false;
        intel.push_back(line);
    }
    return true;
}
/*
bool Criminal::loadCriminal(std::istream& file)
{
    if(!(file >> id))
        return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(!getline(file, name))
        return false;
    if(!(file >> rank))
        return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int intelCount;
    if(!(file >> intelCount))
        return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    intel.clear();
    for(int i = 0; i < intelCount; ++i)
    {
        std::string line;
        if(!getline(file, line))
            return false;
        intel.push_back(line);
    }
    return true;
}
*/

void Criminal::promote(int inc){
    rank += inc;
}

double Criminal::calculateThreatLevel() const{
    double score = rank * 10.0;
    score+= static_cast<double>(intel.size()) * 3.5;
    if (rank>8 && intel.size()>5)
        score*=1.2;
    return score;
}

double Criminal::assessThreat() const {
    return calculateThreatLevel();
}

Criminal::Criminal(const Criminal& other)
    : DatabaseEntry(other), id(other.id), rank(other.rank), intel(other.intel) { ++criminalCount; }

void swap(Criminal& a, Criminal& b) noexcept {
    using std::swap;
    swap(a.name, b.name);
    swap(a.id, b.id);
    swap(a.rank, b.rank);
    swap(a.intel, b.intel);
}

Criminal& Criminal::operator=(Criminal other) {
    swap(*this, other);
    return *this;
}

std::unique_ptr<DatabaseEntry> Criminal::clone() const {
    return std::make_unique<Criminal>(*this);
}

// DatabaseEntry implementations
std::string Criminal::type() const {
    return "Criminal";
}

std::string Criminal::summary() const {
    return "Criminal: " + name + " (Rank: " + std::to_string(rank) + ")";
}


void Criminal::save(std::ostream& out) const {
    out << static_cast<int>(category) << "\n"; // Salvăm tipul pentru MasterFactory
    out << id << "\n";
    out << name << "\n";
    out << rank << "\n";
    out << intel.size() << "\n";
    for(const auto& s : intel) out << s << "\n";
}

bool Criminal::simulateEscape(double facilitySecurityLevel) const{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 100.0);
    const double baseChance = rank * 2.0;
    double escapeChance = baseChance * 10.0 / facilitySecurityLevel;
    if (escapeChance > 100.0) escapeChance = 100.0;
    const double randomValue = distrib(gen);
    std::cout << name << " escape chance: " << escapeChance <<  "% |Roll: " <<randomValue <<"\n";
    return randomValue < escapeChance;
}

// interaction implementation
std::string Criminal::interact(DatabaseEntry& other) {
    // Try dynamic cast to Family
    if(auto* fam = dynamic_cast<Family*>(&other)){
        if(!intel.empty()){
            std::string stolen = intel.back();
            // note: Criminal::intel is private; we mutate here for demo purposes
            // we'll remove last intel and report stealing
            // Since method is const in other places, here we allow changing criminal state
            // by casting away constness is not necessary; this method is non-const
            intel.pop_back();
            return name + " stole intel '" + stolen + "' from " + fam->getCodename();
        } else {
            return name + " tried to steal from " + fam->getCodename() + " but had no intel to trade.";
        }
    }
    // Interact with Batsuit: simple inspect
    if(auto* bs = dynamic_cast<Batsuit*>(&other)){
        return name + " inspects suit part '" + bs->getPart() + "' (integrity: " + std::to_string(bs->getIntegrity()) + ")";
    }
    return name + " has no special interaction with " + other.type();
}
