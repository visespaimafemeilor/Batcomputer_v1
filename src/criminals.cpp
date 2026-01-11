//criminals.cpp
#include "../include/criminals/criminals.h"
#include "family.h"
#include "batsuit.h"
#include "../include/criminals/hacker.h"
#include "../include/criminals/crimeLord.h"
#include "../include/criminals/bank_robber.h"
#include "../include/criminals/metahuman.h"
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

    const auto type = static_cast<CriminalType>(typeInt);
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

void Criminal::showAll(const std::vector<std::shared_ptr<DatabaseEntry>>& db) {
    std::cout << "\n=== ARKHAM ASYLUM RECORDS ===\n";
    bool foundAny = false;

    for (const auto& e : db) {
        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
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
        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
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

void Criminal::promote(int inc){
    rank += inc;
}

void Criminal::promoteByName(const std::vector<std::shared_ptr<DatabaseEntry>>& db, const std::string& name) {
    for (auto& e : db) {
        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
            if (c->getName() == name) {
                c->promote();
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

std::string Criminal::interact(DatabaseEntry& other) {
    if(auto* fam = dynamic_cast<Family*>(&other)){
        if(!intel.empty()){
            std::string stolen = intel.back();
            intel.pop_back();
            return name + " stole intel '" + stolen + "' from " + fam->getCodename();
        } else {
            return name + " tried to steal from " + fam->getCodename() + " but had no intel to trade.";
        }
    }
    if(auto* bs = dynamic_cast<Batsuit*>(&other)){
        return name + " inspects suit part '" + bs->getPart() + "' (integrity: " + std::to_string(bs->getIntegrity()) + ")";
    }
    return name + " has no special interaction with " + other.type();
}

void Criminal::simulateArkhamBlackout(std::vector<std::shared_ptr<DatabaseEntry>>& database, double systemSecurity) {
    std::cout << "\n!!! [ALARM] ARCHAM ASYLUM SYSTEM BREACH DETECTED !!!\n";

    // Pasul 1: Verificam influenta liderilor
    double finalSecurity = systemSecurity;
    for (const auto& entry : database) {
        if (auto lord = std::dynamic_pointer_cast<CrimeLord>(entry)) {
            finalSecurity -= 15.0; // Un Crime Lord scade securitatea cu 15 unitati
            std::cout << "[!] Crime Lord " << lord->getName() << " is coordinating the riots!\n";
        }
    }

    // Pasul 2: Simulam evadarea
    auto it = database.begin();
    int escapeCount = 0;

    while (it != database.end()) {
        if (auto c = std::dynamic_pointer_cast<Criminal>(*it)) {
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
        if (auto c = std::dynamic_pointer_cast<Criminal>(entry)) {
            totalCriminalThreat += c->calculateThreatLevel();
            if (std::dynamic_pointer_cast<Hacker>(entry)) hackerCount++;
        }
        // 2. Analizăm Defensia (Familie)
        else if (auto f = std::dynamic_pointer_cast<Family>(entry)) {
            totalFamilyDefense += f->getPhysicalPower();
            if (f->getName() == "Oracle") oraclePresent = true;
        }
        // 3. Analizăm Resursele (Batsuit)
        else if (auto b = std::dynamic_pointer_cast<Batsuit>(entry)) {
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
    double ratio = totalCriminalThreat / (totalFamilyDefense + 1.0); // +1 pentru a evita împărțirea la 0

    std::cout << "STATUS: ";
    if (ratio < 0.5) std::cout << "GOTHAM IS SECURE. Batman has the situation under control.\n";
    else if (ratio < 1.2) std::cout << "EQUILIBRIUM. Constant vigilance required.\n";
    else if (ratio < 2.0) std::cout << "DANGER. Criminal activity outpaces response capabilities!\n";
    else std::cout << "CRITICAL. Gotham is falling. Call the Justice League.\n";
}

void Criminal::runForensics(const std::vector<std::shared_ptr<DatabaseEntry>>& database) {
    bool oracleProtects = false;
    for (const auto& e : database) {
        if (auto f = std::dynamic_pointer_cast<Family>(e)) {
            if (f->getName() == "Oracle") oracleProtects = true;
        }
    }

    std::cout << "\n--- DIGITAL FORENSICS REPORT ---\n";
    if (oracleProtects) {
        std::cout << "[SAFE] Oracle has encrypted all Bat-Systems. Hackers are powerless.\n";
        return;
    }

    for (const auto& e : database) {
        if (auto h = std::dynamic_pointer_cast<Hacker>(e)) {
            std::cout << "[RISK] Hacker " << h->getName() << " is attempting to breach suit files...\n";
            for (const auto& p : database) {
                if (auto suit = std::dynamic_pointer_cast<Batsuit>(p)) {
                    if (suit->getIntegrity() < 40.0) {
                        std::cout << "  > WARNING: Data leaked from damaged part: " << suit->getName() << "\n";
                    }
                }
            }
        }
    }
}