//criminals.cpp
#include "criminals/criminals.h"
#include "criminals/hacker.h"
#include <algorithm>
#include <limits>
#include <sstream>
#include <random>
#include "family.h"
#include "batsuit.h"

int Criminal::criminalCount = 0;


Criminal::Criminal(const int id_, std::string name_, const int rank_, const std::vector<std::string>& intel_, const CriminalType cat) :
    DatabaseEntry(std::move(name_)),
    id{id_},
    rank{rank_},
    intel{intel_},
    category{cat}
{ ++criminalCount; }

Criminal::~Criminal() { --criminalCount; }

Criminal::Criminal(const Criminal& other)
    : DatabaseEntry(other),
      id(other.id),
      rank(other.rank),
      intel(other.intel),
      category(other.category)
{
    ++criminalCount;
}

std::ostream& operator<<(std::ostream& os, const Criminal& cr)
{
    os<<"Id: "<<cr.id<< " Codename: "<<cr.name<<"\n";
    os<<"Rank: "<<cr.rank<<"\n";
    return os;
}

void Criminal::doDisplay(std::ostream& os) const {
    os << "-- CRIMINAL: " << name << " (Rank: " << rank << ") --\n";
}

int Criminal::getId() const {return id;}
//const string& Criminal::getName() const  { return name; }
int Criminal::getRank() const  { return rank; }
const std::vector<std::string>& Criminal::getIntel() const  { return intel; }

bool Criminal::load(std::istream& in) {
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

void Criminal::showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db) {
    std::cout << "\n=== ARKHAM ASYLUM RECORDS ===\n";
    bool foundAny = false;

    for (const auto& e : db) {
        if (const Criminal* c = e->asCriminal()) {
            c->displayInfo();
            std::cout << "Rank: " << c->getRank()
                      << " | Threat: " << c->calculateThreatLevel() << "\n";

            if (!c->specialty().empty()) {
                std::cout << "Specialty: " << c->specialty() << "\n";
            }
            std::cout << "--------------------------\n";
            foundAny = true;
        }
    }

    if (!foundAny) {
        std::cout << "No criminal records found in the current database.\n";
    }
}

void Criminal::searchByName(const std::vector<std::shared_ptr<DatabaseEntry>>& db, const std::string& name) {
    bool found = false;
    for (const auto& e : db) {
        if (const Criminal* c = e->asCriminal()) {
            if (c->getName() == name) {
                std::cout << "[FOUND] ";
                c->displayInfo();
                std::cout << "Intel count: " << c->getIntel().size() << "\n";
                found = true;
                break;
            }
        }
    }
    if (!found) std::cout << "Criminal '" << name << "' not found in records.\n";
}

void Criminal::promote(const int inc){
    rank += inc;
}

void Criminal::promoteByName(const std::vector<std::shared_ptr<DatabaseEntry>>& db, const std::string& name) {
    for (auto& e : db) {
        if (const Criminal* c = e->asCriminal()) {
            if (c->getName() == name) {
                // promote() modifies the object; obtain non-const pointer
                if (auto* modc = e->asCriminal()) modc->promote();
                std::cout << "[UPDATE] " << name << " has been promoted to Rank " << c->getRank() << ".\n";
                return;
            }
        }
    }
    std::cout << "Target not found for promotion.\n";
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

bool Criminal::simulateEscape(const double facilitySecurityLevel) const{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution distrib(0.0, 100.0);
    const double baseChance = rank * 2.0;
    double escapeChance = baseChance * 10.0 / facilitySecurityLevel;
    if (escapeChance > 100.0) escapeChance = 100.0;
    const double randomValue = distrib(gen);
    std::cout << name << " escape chance: " << escapeChance <<  "% |Roll: " <<randomValue <<"\n";
    return randomValue < escapeChance;
}

std::string Criminal::interact(DatabaseEntry& other) {
    if(const std::string resp = other.interactedBy(*this); !resp.empty()) return resp;
    return name + " has no special interaction with " + other.type();
}

std::string Criminal::interactedBy(const Family& f) {
    if(!intel.empty()){
        const std::string stolen = intel.back();
        intel.pop_back();
        return name + " stole intel '" + stolen + "' from " + f.getCodename();
    }
    return name + " tried to steal from " + f.getCodename() + " but had no intel to trade.";
}

std::string Criminal::interactedBy(const Batsuit& b) {
    return name + " inspects suit part '" + b.getPart() + "' (integrity: " + std::to_string(b.getIntegrity()) + ")";
}

void Criminal::simulateArkhamBlackout(std::vector<std::shared_ptr<DatabaseEntry>>& database, const double systemSecurity) {
    std::cout << "\n!!! [ALARM] ARCHAM ASYLUM SYSTEM BREACH DETECTED !!!\n";

    // Pasul 1: Verificam influenta liderilor
    double finalSecurity = systemSecurity;
    for (const auto& entry : database) {
        if (const Criminal* c = entry->asCriminal()) {
            c->affectBlackoutSecurity(finalSecurity);
        }
    }

    // Pasul 2: Simulam evadarea
    auto it = database.begin();
    int escapeCount = 0;

    while (it != database.end()) {
        if (const Criminal* c = (*it)->asCriminal()) {
            if (c->simulateEscape(finalSecurity)) {
                std::cout << "[OUTBREAK] " << c->getName() << " (Rank " << c->getRank() << ") has escaped!\n";
                it = database.erase(it); // il stergem din baza de date (a fugit)
                escapeCount++;
                continue;
            }
        }
        ++it;
    }

    std::cout << "\n[REPORT] Outbreak contained. Total escaped: " << escapeCount << "\n";
    if (escapeCount > 0) std::cout << "[WARNING] Gotham PD warns citizens to stay indoors.\n";
}

void Criminal::generateStrategicReport(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    double totalCriminalThreat = 0;
    double totalFamilyDefense = 0;
    int hackerCount = 0;
    bool oraclePresent = false;
    int brokenParts = 0;

    std::cout << "\n--- [BAT-COMPUTER STRATEGIC ANALYSIS] ---\n";

    for (const auto& entry : database) {
        // 1. Analizăm Amenințarea (Criminali)
        if (const Criminal* c = entry->asCriminal()) {
            totalCriminalThreat += c->calculateThreatLevel();
            hackerCount += c->hackerCountContribution();
        }
        // 2. Analizăm Defensia (Familie)
        else if (const Family* f = entry->asFamily()) {
            totalFamilyDefense += f->getPhysicalPower();
            if (f->getName() == "Oracle") oraclePresent = true;
        }
        // 3. Analizăm Resursele (Batsuit)
        else if (const Batsuit* b = entry->asBatsuit()) {
            if (b->getIntegrity() < 50.0) brokenParts++;
        }
    }

    // --- LOGICA DE CALCUL A RISCULUI ---

    // Riscul crește dacă avem mulți Hackeri și nu avem Oracle pentru contramăsuri
    if (hackerCount > 0 && !oraclePresent) {
        totalCriminalThreat *= 1.3;
        std::cout << "[!] WARNING: Digital vulnerability detected. Hackers are unmonitored!\n";
    }

    // Riscul crește dacă Batman are costumul distrus
    if (brokenParts > 2) {
        totalFamilyDefense *= 0.8;
        std::cout << "[!] WARNING: Batsuit integrity is compromised. Frontline efficiency lowered.\n";
    }

    std::cout << "\nGlobal Threat Level: " << totalCriminalThreat << "\n";
    std::cout << "Global Defense Level: " << totalFamilyDefense << "\n";

    // --- CONCLUZIA ---
    const double ratio = totalCriminalThreat / (totalFamilyDefense + 1.0); // +1 pentru a evita împărțirea la 0

    std::cout << "STATUS: ";
    if (ratio < 0.5) std::cout << "GOTHAM IS SECURE. Batman has the situation under control.\n";
    else if (ratio < 1.2) std::cout << "EQUILIBRIUM. Constant vigilance required.\n";
    else if (ratio < 2.0) std::cout << "DANGER. Criminal activity outpaces response capabilities!\n";
    else std::cout << "CRITICAL. Gotham is falling. Call the Justice League.\n";
}

void Criminal::runForensics(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    bool oracleProtects = false;
    for (const auto& e : database) {
        if (const Family* f = e->asFamily()) {
            if (f->getName() == "Oracle") oracleProtects = true;
        }
    }

    std::cout << "\n--- DIGITAL FORENSICS REPORT ---\n";
    if (oracleProtects) {
        std::cout << "[SAFE] Oracle has encrypted all Bat-Systems. Hackers are powerless.\n";
        return;
    }

    for (const auto& e : database) {
        if (const Criminal* c = e->asCriminal()) {
            c->runForensicsAction(database);
        }
    }
}