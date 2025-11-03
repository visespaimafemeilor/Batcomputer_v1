#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>
#include <random>

class Criminal{
private:
    int id;
    std::string name;
    int rank;
    std::vector<std::string> intel;

public:
    explicit Criminal(int id_ = 1, std::string  name_ = "cr", int rank_ = 1, const std::vector<std::string>& intel_ = {"intel 1"}) :
        id{id_},
        name{std::move(name_)},
        rank{rank_},
        intel{intel_}
    {
        //initialization constructor
    }

    Criminal(const Criminal& other) = default;  //copy constructor

    Criminal& operator=(const Criminal& other) = default;

    ~Criminal() = default; //destructor

    friend std::ostream& operator<<(std::ostream& os, const Criminal& cr)
    {
        os<<"Id: "<<cr.id<< "Codename: "<<cr.name<<"\n";
        os<<"Rank: "<<cr.rank<<"\n";
        return os;
    }

    [[nodiscard]] int getId() const {return id;}
    [[nodiscard]] const std::string& getName() const  { return name; }
    [[nodiscard]] int getRank() const  { return rank; }
    [[nodiscard]] const std::vector<std::string>& getIntel() const  { return intel; }

    bool loadCriminal(std::istream& file)
    {
        if(!(file >> id))
            return false;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(!std::getline(file, name))
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
            if(!std::getline(file, line))
                return false;
            intel.push_back(line);
        }
        return true;
    }
/*
    void showIntel() const{
        std::cout<<"Intel report for "<<name<<":\n";
        for(const auto & i : intel)
        {
            std::cout<<"--> "<<i<<"\n";
        }
    }
*/
    void promote(int inc=1){
        rank += inc;
    }

    [[nodiscard]]double calculateThreatLevel() const{
        double score = rank * 10.0;
        score+= static_cast<double>(intel.size()) * 3.5; //fiecare informatie despre criminal adauga un risc
        if (rank>8 && intel.size()>5)
            score*=1.2; //da boost la scor daca e criminal mare cu multe informatii despre el
        return score;
    }

    [[nodiscard]]bool simulateEscape(double facilitySecurityLevel) const{
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

};

class Family
{
private:
    std::string codename;
    std::string civilian_name;
    int physical_power;
    std::vector<std::string> skills;

public:
    explicit Family(std::string  codename_ = "mem", std::string  civilian_name_ = "mem", int physical_power_ = 1, const std::vector<std::string>& skills_ = {"skill"}) :
        codename{std::move(codename_)},
        civilian_name{std::move(civilian_name_)},
        physical_power{physical_power_},
        skills{skills_}
    {
//        std::cout<<"Initialization constructor for Family\n";
    }

    Family(const Family& other) :
        codename{other.codename},
        civilian_name{other.civilian_name},
        physical_power {other.physical_power},
        skills {other.skills}
    {
//        std::cout << "Copy contructor for Family\n";
    }

    Family& operator=(const Family& other) {
        codename = other.codename;
        civilian_name = other.civilian_name;
        physical_power = other.physical_power;
        skills = other.skills;
//        std::cout << "operator= copiere Family\n";
        return *this;
    }

    ~Family(){
//        std::cout << "Destructor Family\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Family& f)
    {
        os<<"Name: "<<f.civilian_name<<" AKA "<<f.codename<<"\n";
        os<<"Power: "<<f.physical_power<<"\n";
        return os;
    }

    [[nodiscard]] const std::string& getCodename() const {return codename;}
    [[nodiscard]] const std::string& getCivilianName() const {return civilian_name;}
    [[nodiscard]] int getPhysicalPower() const {return physical_power;}
    [[nodiscard]] const std::vector<std::string>& getSkills() const {return skills;}

    bool loadFamilyMember(std::istream& file)
    {
        file >> std::ws;
        if(!std::getline(file, codename))
            return false;
        if(codename.empty())
            return false;
        file >> std::ws;
        if(!std::getline(file, civilian_name))
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
            if(!std::getline(file, s))
                return false;
            if(!s.empty())
                skills.push_back(s);
        }
        return true;
    }


    [[nodiscard]] bool fight(const Criminal& enemy) const{
        return physical_power>enemy.getRank();
    }

    [[nodiscard]] std::string fightReport(const Criminal& enemy) const{
        std::string report = codename + " vs " + enemy.getName() + "\n";
        report += "Power: " + std::to_string(physical_power) + " vs Rank: " + std::to_string(enemy.getRank()) + "\n";
        if (fight(enemy)){
            report+= "Result: Victory\n";
        }
        else{
            report+="Result: Defeat\n";
        }
        return report;
    }

    [[nodiscard]] std::string simulateBattle(const Criminal& enemy) const{
        int myPower=physical_power;
        int enemyPower=enemy.getRank()*10;
        int round = 0;
        std::ostringstream report;

        report << "Battle: " <<codename << " VS "<<enemy.getName()<<"\n";

        static std::random_device rd; //am folosit asta ca imi dadea warning ca foloseam rand()
        static std::mt19937 gen(rd());
        while (myPower>0 && enemyPower>0){
            round++;

            std::uniform_int_distribution<> myHitDistrib(5, 20);
            std::uniform_int_distribution<> enemyHitDistrib(3, 15);

            int myHit = myHitDistrib(gen);
            int enemyHit = enemyHitDistrib(gen);
            enemyPower -= myHit;
            myPower -= enemyHit;
            report << "Round "<<round<<": "<<codename<<" hits "<<myHit<<" | "<<enemy.getName()<<" hits "<<enemyHit<<"\n";
        }
        report<<"Winner: "<<(myPower>0 ? codename : enemy.getName())<<"\n";
        return report.str();

    }

};

class Batsuit{
private:
    int level;
    std::string part;
    double integrity; //daca mai tine

    void normalize(){
        if (level<1) level =1;
        if (integrity<0) integrity=0;
        if (integrity>100) integrity=100;
    }

public:
    explicit Batsuit(int level_ = 1, std::string  part_ = "p", double integrity_ = 1.00) :
        level{level_},
        part{std::move(part_)},
        integrity{integrity_}
    {
//        initialization constructor
    }

    Batsuit(const Batsuit& other) = default;

    Batsuit& operator= (const Batsuit& other) = default;

    ~Batsuit() = default;

    friend std::ostream& operator<<(std::ostream& os, const Batsuit& bs)
    {
        os<<"Suit part: "<<bs.part<<"\n";
        os<<"Level: "<<bs.level<< "--- Integrity: "<<bs.integrity<<"\n";
        return os;
    }

    [[nodiscard]] int getLevel() const {return level;}
    [[nodiscard]] const std::string& getPart() const {return part;}
    [[nodiscard]] double getIntegrity() const {return integrity;}

    bool loadBatsuit(std::istream& file)
    {
        if(!(file >> level))
            return false;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(!std::getline(file, part))
            return false;
        if(!(file >> integrity))
            return false;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        normalize(); //asta ca sa ma asigur ca nu pun vreo prostie in fisiere
        return true;
    }

    [[nodiscard]] bool isCritical(double muchie=30.0) const{
        return integrity<muchie;
    }

    [[nodiscard]] std::string statusReport() const{
        std::string status = "Batsuit part: " + part +"\n";
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

    void applyBattleDamage(int damageBad){
        const double degradation = damageBad / static_cast<double>(level);
        integrity-=degradation;
        if (integrity<0) integrity=0;
        std::cout << "Batsuit took "<<degradation<<"% damage! Integrity now at "<<integrity<<"%\n";
    }

};

class Batman {
private:
    std::string alias;
    Batsuit suit;
    std::vector<Family> allies;
    std::vector<Criminal> enemies;

public:
    Batman(std::string alias_, const Batsuit& suit_,
           const std::vector<Family>& allies_,
           const std::vector<Criminal>& enemies_)
        : alias(std::move(alias_)), suit(suit_), allies(allies_), enemies(enemies_) {}


    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Batman& b) {
        os << "=== BATMAN PROFILE ===\n";
        os << "Alias: " << b.alias << "\n\n";
        os << "--- Batsuit ---\n" << b.suit << "\n";
        os << "--- Allies ---\n";
        for (const auto& f : b.allies)
            os << f << "\n";
        os << "--- Known Criminals ---\n";
        for (const auto& c : b.enemies)
            os << c << "\n";
        return os;
    }
};


int main(){

    std::cout<<"Welcome, Dark Knight!\n";

    std::vector<Criminal> criminals;
    std::vector<Family> family;
    std::vector<Batsuit> suit;

    std::ifstream file1("criminals.txt");
    std::ifstream file2("family.txt");
    std::ifstream file3("batsuit.txt");

    if(!file1 || !file2 || !file3){
        std::cerr << "One or more files could not be opened.\n";
        return 1;
    }

    //load criminals
    while(true) {
        Criminal c;
        if(!c.loadCriminal(file1)) break;
        criminals.push_back(c);
    }

    //load family members
    while(true) {
        Family m;
        if(!m.loadFamilyMember(file2)) break;
        family.push_back(m);
    }

    //load batsuit
    while(true) {
        Batsuit b;
        if(!b.loadBatsuit(file3)) break;
        suit.push_back(b);
    }

    Batsuit mainSuit = suit.empty() ? Batsuit() : suit[0];
    Batman bruce("The Dark Knight", mainSuit, family, criminals);

    std::cout << "\n\n" << bruce;

    //TODO: MENIU
    int choice = -1;
    while(choice != 0)
    {
        std::cout << "\n==========================\n";
        std::cout << "        BAT-COMPUTER      \n";
        std::cout << "==========================\n";
        std::cout << "1) Show Criminal Database (using getters)\n";
        std::cout << "2) Show Bat-Family Members (using getters)\n";
        std::cout << "3) Show Batsuit Loadout (using getters)\n";
        std::cout << "4) Show criminal intel\n";
        std::cout << "5) Search Criminal by Name\n";
        std::cout << "6) Search Family Member by Codename\n";
        std::cout << "7) Simulate battle (fightReport + simulateBattle)\n";
        std::cout << "8) Show Batsuit status report & simulate damage\n";
        std::cout << "9) Promote Criminal & Show Threat Level\n";
        std::cout << "10) Simulate Escape Attempt\n";
        std::cout << "0) Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice)
        {
            case 1:{
                std::cout << "\n=== Criminal Database ===\n";
                for(const auto& c : criminals){
                    std::cout << "ID: " << c.getId() << "\n";
                    std::cout << "Name: " << c.getName() << "\n";
                    std::cout << "Rank: " << c.getRank() << "\n";
                    std::cout << "Intel count: " << c.getIntel().size() << "\n";
                    std::cout << "Threat Level: " << c.calculateThreatLevel() << "\n\n";
                }
                break;
            }

            case 2:{
                std::cout << "\n=== Bat-Family Members ===\n";
                for(const auto& f : family){
                    std::cout << "Codename: " << f.getCodename() << "\n";
                    std::cout << "Civilian Name: " << f.getCivilianName() << "\n";
                    std::cout << "Physical Power: " << f.getPhysicalPower() << "\n";
                    std::cout << "Skills: ";
                    for(const auto& skill : f.getSkills())
                        std::cout << skill << ", ";
                    std::cout << "\n\n";
                }
                break;
            }

            case 3:{
                std::cout << "\n=== Batsuit Loadout ===\n";
                for(const auto& b : suit){
                    std::cout << "Part: " << b.getPart() << "\n";
                    std::cout << "Level: " << b.getLevel() << "\n";
                    std::cout << "Integrity: " << b.getIntegrity() << "\n\n";
                }
                break;
            }

            case 4:{
                    std::cout << "\nEnter criminal name for intel: ";
                    std::string name;
                    std::getline(std::cin, name);
                    bool found = false;
                    for(const auto& c : criminals){
                        if(c.getName() == name){
                            found = true;
                            const auto& intel = c.getIntel();
                            std::cout << "\nIntel report for " << c.getName() << ":\n";
                            if(intel.empty()){
                                std::cout << "No intel available.\n";
                            } else {
                                for(const auto & i : intel){
                                    std::cout<<"--> "<< i<<"\n";
                                }
                            }
                            break;
                        }
                    }
                    if(!found)
                        std::cout << "No criminal found with that name.\n";
                    break;
            }


            case 5:{
                std::cout << "\nEnter criminal name: ";
                std::string searchName;
                std::getline(std::cin, searchName);
                bool found = false;
                for(const auto& c : criminals){
                    if(c.getName() == searchName){
                        std::cout << "FOUND:\n";
                        std::cout << "ID: " << c.getId() << "\n";
                        std::cout << "Name: " << c.getName() << "\n";
                        std::cout << "Rank: " << c.getRank() << "\n";
                        std::cout << "Threat Level: " << c.calculateThreatLevel() << "\n\n";
                        found = true;
                    }
                }
                if(!found) std::cout << "No criminal found with that name.\n";
                break;
            }

            case 6:{
                std::cout << "\nEnter codename: ";
                std::string code;
                std::getline(std::cin, code);
                bool found = false;
                for(const auto& f : family){
                    if(f.getCodename() == code){
                        std::cout << "FOUND:\n";
                        std::cout << "Codename: " << f.getCodename() << "\n";
                        std::cout << "Civilian Name: " << f.getCivilianName() << "\n";
                        std::cout << "Physical Power: " << f.getPhysicalPower() << "\n";
                        std::cout << "Skills: ";
                        for(const auto& skill : f.getSkills())
                            std::cout << skill << ", ";
                        std::cout << "\n\n";
                        found = true;
                    }
                }
                if(!found) std::cout << "No family member found.\n";
                break;
            }

            case 7:{
                std::cout << "\nChoose family member (codename): ";
                std::string codename;
                std::getline(std::cin, codename);
                std::cout << "Choose criminal: ";
                std::string cname;
                std::getline(std::cin, cname);

                const Family* vigillante = nullptr;
                const Criminal* enemy = nullptr;

                for(const auto& f : family)
                    if(f.getCodename() == codename) vigillante = &f;
                for(const auto& c : criminals)
                    if(c.getName() == cname) enemy = &c;

                if(vigillante && enemy){
                    std::cout << vigillante->getCodename() << " (Power: "
                              << vigillante->getPhysicalPower() << ") "
                              << "VS " << enemy->getName() << " (Rank: "
                              << enemy->getRank() << ")\n";

                    std::cout << vigillante->fightReport(*enemy);
                    std::cout << vigillante->simulateBattle(*enemy);
                }
                else
                    std::cout << "Invalid names.\n";
                break;
            }

            case 8:{
                std::cout << "\nBatsuit Status Report\n";
                for(auto& b : suit){
                    std::cout << b.statusReport() << "\n";
                    // Simulăm o lovitură
                    b.applyBattleDamage(10);
                    std::cout << "After damage: " << b.statusReport() << "\n";
                }
                break;
            }

            case 9:{
                std::cout << "\nEnter criminal name to promote: ";
                std::string name;
                std::getline(std::cin, name);
                bool found = false;
                for(auto& c : criminals){
                    if(c.getName() == name){
                        c.promote();
                        std::cout << "Criminal promoted!\n";
                        std::cout << "New Rank: " << c.getRank() << "\n";
                        std::cout << "Threat Level: " << c.calculateThreatLevel() << "\n";
                        found = true;
                        break;
                    }
                }
                if(!found) std::cout << "No such criminal.\n";
                break;
            }

            case 10:{
                std::cout << "\nEnter criminal name for escape simulation: ";
                std::string name;
                std::getline(std::cin, name);
                double securityLevel;
                std::cout << "Enter facility security level (1-10): ";
                std::cin >> securityLevel;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bool found = false;
                for(const auto& c : criminals){
                    if(c.getName() == name){
                        found = true;
                        bool escaped = c.simulateEscape(securityLevel);
                        std::cout << (escaped ? "ESCAPED!" : "Contained.") << "\n";
                        break;
                    }
                }
                if(!found) std::cout << "No such criminal.\n";
                break;
            }

            case 0:
                std::cout << "\nExiting Bat-Computer... Stay vigilant.\n";
                break;

            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
