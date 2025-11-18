#include "batsuit.h"

using namespace std;

void Batsuit::normalize(){
    if (level<1) level =1;
    if (integrity<0) integrity=0;
    if (integrity>100) integrity=100;
}

Batsuit::Batsuit(int level_, string part_, double integrity_) :
    level{level_},
    part{std::move(part_)},
    integrity{integrity_}
{}

ostream& operator<<(ostream& os, const Batsuit& bs)
{
    os<<"Suit part: "<<bs.part<<"\n";
    os<<"Level: "<<bs.level<< "--- Integrity: "<<bs.integrity<<"\n";
    return os;
}

int Batsuit::getLevel() const {return level;}
const string& Batsuit::getPart() const {return part;}
double Batsuit::getIntegrity() const {return integrity;}

bool Batsuit::loadBatsuit(istream& file)
{
    if(!(file >> level))
        return false;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    if(!getline(file, part))
        return false;
    if(!(file >> integrity))
        return false;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    normalize();
    return true;
}

bool Batsuit::isCritical(double muchie) const{
    return integrity<muchie;
}

string Batsuit::statusReport() const{
    string status = "Batsuit part: " + part +"\n";
    status+="Level: "+to_string(level)+"\n";
    status+="Integrity: "+to_string(integrity)+"\n";
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
    cout << "Batsuit took "<<degradation<<"% damage! Integrity now at "<<integrity<<"%\n";
}