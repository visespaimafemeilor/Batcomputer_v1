//criminals.cpp
#include "criminals.h"
#include <memory>
#include <utility>

int Criminal::criminalCount = 0;

Criminal::Criminal(int id_, std::string name_, int rank_, const std::vector<std::string>& intel_) :
    DatabaseEntry(std::move(name_)),
    id{id_},
    rank{rank_},
    intel{intel_}
{ ++criminalCount; }

Criminal::~Criminal() { --criminalCount; }


std::ostream& operator<<(std::ostream& os, const Criminal& cr)
{
    os<<"Id: "<<cr.id<< "Codename: "<<cr.name<<"\n";
    os<<"Rank: "<<cr.rank<<"\n";
    return os;
}

int Criminal::getId() const {return id;}
//const string& Criminal::getName() const  { return name; }
int Criminal::getRank() const  { return rank; }
const std::vector<std::string>& Criminal::getIntel() const  { return intel; }

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
    return std::string("Criminal");
}

std::string Criminal::summary() const {
    return "Criminal: " + name + " (Rank: " + std::to_string(rank) + ")";
}

bool Criminal::load(std::istream& in) {
    return loadCriminal(in);
}

void Criminal::save(std::ostream& out) const {
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
