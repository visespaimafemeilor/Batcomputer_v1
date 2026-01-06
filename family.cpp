//family.cpp
#include "family.h"
#include <memory>

Family::Family(std::string codename_, std::string civilian_name_, int physical_power_, const std::vector<std::string>& skills_) :
    DatabaseEntry(std::move(codename_)),
    civilian_name{std::move(civilian_name_)},
    physical_power{physical_power_},
    skills{skills_}
{}

Family::Family(const Family& other) :
    DatabaseEntry(other),
    civilian_name(other.civilian_name),
    physical_power(other.physical_power),
    skills(other.skills)
{}

void swap(Family& a, Family& b) noexcept {
    using std::swap;
    swap(a.name, b.name);
    swap(a.civilian_name, b.civilian_name);
    swap(a.physical_power, b.physical_power);
    swap(a.skills, b.skills);
}

Family& Family::operator=(Family other) {
    swap(*this, other);
    return *this;
}

std::unique_ptr<DatabaseEntry> Family::clone() const {
    return std::make_unique<Family>(*this);
}

// DatabaseEntry implementations
std::string Family::type() const {
    return std::string("Family");
}

std::string Family::summary() const {
    return "Family member: " + name + " (Civilian: " + civilian_name + ")";
}

bool Family::load(std::istream& in) {
    return loadFamilyMember(in);
}

void Family::save(std::ostream& out) const {
    out << name << "\n";
    out << civilian_name << "\n";
    out << physical_power << "\n";
    out << skills.size() << "\n";
    for(const auto& s : skills) out << s << "\n";
}

std::ostream& operator<<(std::ostream& os, const Family& f)
{
    os<<"Name: "<<f.civilian_name<<" AKA "<<f.name<<"\n";
    os<<"Power: "<<f.physical_power<<"\n";
    return os;
}

double Family::assessThreat() const {
    return physical_power * 8.0 + static_cast<double>(skills.size()) * 5.0;
}

const std::string& Family::getCodename() const {return name;}
const std::string& Family::getCivilianName() const {return civilian_name;}
int Family::getPhysicalPower() const {return physical_power;}
const std::vector<std::string>& Family::getSkills() const {return skills;}

bool Family::loadFamilyMember(std::istream& file)
{
    file >> std::ws;
    if(!getline(file, name))
        return false;
    if(name.empty())
        return false;
    file >> std::ws;
    if(!getline(file, civilian_name))
        return false;
    if(civilian_name.empty())
        return false;
    if(!(file >> physical_power))
        return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int skillCount;
    if(!(file >> skillCount))
        return false;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (physical_power < 0) physical_power = 0;
    if (skillCount < 0) skillCount = 0;
    skills.clear();
    for(int i = 0; i < skillCount; ++i)
    {
        file >> std::ws;
        std::string s;
        if(!getline(file, s))
            return false;
        if(!s.empty())
            skills.push_back(s);
    }
    return true;
}

bool Family::fight(const Criminal& enemy) const{
    return physical_power>enemy.getRank();
}

std::string Family::fightReport(const Criminal& enemy) const{
    std::string report = name + " vs " + enemy.getName() + "\n";
    report += "Power: " + std::to_string(physical_power) + " vs Rank: " + std::to_string(enemy.getRank()) + "\n";
    if (fight(enemy)){
        report+= "Result: Victory\n";
    }
    else{
        report+="Result: Defeat\n";
    }
    return report;
}

std::string Family::simulateBattle(const Criminal& enemy) const{
    int myPower=physical_power;
    int enemyPower=enemy.getRank()*10;
    int round = 0;
    std::ostringstream report;

    report << "Battle: " <<name << " VS "<<enemy.getName()<<"\n";

    static std::random_device rd;
    static std::mt19937 gen(rd());

    while (myPower>0 && enemyPower>0){
        round++;

        std::uniform_int_distribution<> myHitDistrib(5, 20);
        std::uniform_int_distribution<> enemyHitDistrib(3, 15);

        int myHit = myHitDistrib(gen);
        int enemyHit = enemyHitDistrib(gen);
        enemyPower -= myHit;
        myPower -= enemyHit;
        report << "Round "<<round<<": "<<name<<" hits "<<myHit<<" | "<<enemy.getName()<<" hits "<<enemyHit<<"\n";
    }
    report<<"Winner: "<<(myPower>0 ? name : enemy.getName())<<"\n";
    return report.str();
}