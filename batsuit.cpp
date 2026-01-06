//batsuit.cpp
#include "batsuit.h"
#include <memory>
#include <utility>


void Batsuit::normalize(){
    if (level<1) level =1;
    if (integrity<0) integrity=0;
    if (integrity>100) integrity=100;
}

Batsuit::Batsuit(int level_, std::string part_, double integrity_) :
    DatabaseEntry(std::move(part_)),
    level{level_},
    //part{std::move(part_)},
    integrity{integrity_}
{}

std::ostream& operator<<(std::ostream& os, const Batsuit& bs)
{
    os<<"Suit part: "<<bs.name<<"\n";
    os<<"Level: "<<bs.level<< "--- Integrity: "<<bs.integrity<<"\n";
    return os;
}

double Batsuit::assessThreat() const {
    return (100.0 - integrity) * static_cast<double>(level) * 0.5;
}

Batsuit::Batsuit(const Batsuit& other)
    : DatabaseEntry(other), level(other.level), integrity(other.integrity) {}

void swap(Batsuit& a, Batsuit& b) noexcept {
    using std::swap;
    swap(a.name, b.name);
    swap(a.level, b.level);
    swap(a.integrity, b.integrity);
}


Batsuit& Batsuit::operator=(Batsuit other) {
    swap(*this, other);
    return *this;
}

std::unique_ptr<DatabaseEntry> Batsuit::clone() const {
    return std::make_unique<Batsuit>(*this);
}

// DatabaseEntry implementations
std::string Batsuit::type() const {
    return std::string("Batsuit");
}

std::string Batsuit::summary() const {
    return "Batsuit part: " + name + " (Integrity: " + std::to_string(integrity) + ")";
}

bool Batsuit::load(std::istream& in) {
    return loadBatsuit(in);
}

void Batsuit::save(std::ostream& out) const {
    out << level << "\n";
    out << name << "\n";
    out << integrity << "\n";
}

int Batsuit::getLevel() const {return level;}
const std::string& Batsuit::getPart() const {return name;}
double Batsuit::getIntegrity() const {return integrity;}

bool Batsuit::loadBatsuit(std::istream& file)
{
    if(!(file >> level))
        return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(!getline(file, name))
        return false;
    if(!(file >> integrity))
        return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    normalize();
    return true;
}

bool Batsuit::isCritical(double muchie) const{
    return integrity<muchie;
}

std::string Batsuit::statusReport() const{
    std::string status = "Batsuit part: " + name +"\n";
    status+="Level: "+std::to_string(level)+"\n";
    status+="Integrity: "+std::to_string(integrity)+"\n";
    if(isCritical())
        status+="ALERT! Critical condition!\n";
    else if (integrity<70)
        status +="Moderate condition\n";
    else
        status +="Suit is in good condition\n";
    return status;
}

void Batsuit::applyBattleDamage(int damageBad){
    const double degradation = damageBad / static_cast<double>(level);
    integrity-=degradation;
    if (integrity<0) integrity=0;
    std::cout << "Batsuit took "<<degradation<<"% damage! Integrity now at "<<integrity<<"%\n";
}
