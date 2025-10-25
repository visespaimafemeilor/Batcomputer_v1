#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

class Criminal{
private:
    int id;
    std::string name;
    int rank;
    std::vector<std::string> intel;

public:
    Criminal(int id_ = 1, const std::string& name_ = "cr", int rank_ = 1, const std::vector<std::string>& intel_ = {"intel 1"}) :
        id{id_},
        name{name_},
        rank{rank_},
        intel{intel_}
    {
//        std::cout<<"Initialization constructor for Criminals\n";
    }

    Criminal(const Criminal& other) : id{other.id}, name{other.name}, rank{other.rank}, intel {other.intel}{
//        std::cout << "Copy contructor for Criminal\n";
    }

    Criminal& operator=(const Criminal& other) {
        id = other.id;
        name = other.name;
        rank = other.rank;
        intel = other.intel;
//        std::cout << "operator= copiere Criminal\n";
        return *this;
    }

    ~Criminal() {
//        std::cout << "Destructor Criminal\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Criminal& cr)
    {
        os<<"Id: "<<cr.id<< "Codename: "<<cr.name<<"\n";
        os<<"Rank: "<<cr.rank<<"\n";
        return os;
    }

    int getId() const {return id;}
    const std::string& getName() const  { return name; }
    int getRank() const  { return rank; }
    const std::vector<std::string>& getIntel() const  { return intel; }

    void loadCriminals(std::istream& file)
    {
        file >> id;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(file, name);
        file >> rank;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int intelCount;
        file >> intelCount;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        intel.clear();
        for(int i = 0; i < intelCount; ++i) {
            std::string line;
            std::getline(file, line);
            intel.push_back(line);
        }

        std::string throwaway;
        std::getline(file, throwaway);
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
    Family(const std::string& codename_ = "mem", const std::string& civilian_name_ = "mem", int physical_power_ = 1, const std::vector<std::string>& skills_ = {"skill"}) :
        codename{codename_},
        civilian_name{civilian_name_},
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

    const std::string& getCodename() const {return codename;}
    const std::string& getCivilianName() const {return civilian_name;}
    int getPhysicalPower() const {return physical_power;}
    const std::vector<std::string>& getSkills() const {return skills;}

    void loadFamilyMember(std::istream& file)
    {
        // Sărim peste linii goale dintre intrări
        do {
            if(!std::getline(file, codename)) return; // Dacă nu mai avem ce citi -> ieșim
        } while (codename.empty());

        std::getline(file, civilian_name);

        file >> physical_power;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int skillCount;
        file >> skillCount;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        skills.clear();
        for(int i = 0; i < skillCount; ++i) {
            std::string s;
            std::getline(file, s);
            skills.push_back(s);
        }
    }

};

class Batsuit
{
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
    Batsuit(int level_ = 1, const std::string& part_ = "p", double integrity_ = 1.00) :
        level{level_},
        part{part_},
        integrity{integrity_}
    {
//        std::cout<< "Contructor initialization for Batsuit\n";
    }

    Batsuit(const Batsuit& other) : level{other.level}, part{other.part}, integrity {other.integrity}{
//        std::cout << "Copy constructor for Batsuit\n";
    }

    Batsuit& operator=(const Batsuit& other) {
        level = other.level;
        part = other.part;
        integrity = other.integrity;
//        std::cout << "operator= copiere Batsuit\n";
        return *this;
    }

    ~Batsuit(){
//        std::cout << "Destructor Batsuit\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Batsuit& bs)
    {
        os<<"Suit part: "<<bs.part<<"\n";
        os<<"Level: "<<bs.level<< "--- Integrity: "<<bs.integrity<<"\n";
        return os;
    }

    int getLevel() const {return level;}
    const std::string& getPart() const {return part;}
    double getIntegrity() const {return integrity;}

    void loadBatsuit(std::istream& file)
    {
        file >> level;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(file, part);
        file >> integrity;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        normalize();

        std::string throwaway;
        std::getline(file, throwaway);
    }
};

int main(){

    std::cout<<"Welcome, Dark Knight!\n";

    std::vector<Criminal> criminals;
    std::vector<Family> family;
    std::vector<Batsuit> suit;

    std::ifstream file1("C:/Projects/UB POO/oop-template-main/criminals.txt");
    std::ifstream file2("C:/Projects/UB POO/oop-template-main/family.txt");
    std::ifstream file3("C:/Projects/UB POO/oop-template-main/batsuit.txt");

    if(!file1 || !file2 || !file3){
        std::cerr << "One or more files could not be opened.\n";
        return 1;
    }
    // --- Load Criminals ---
    while(true) {
        Criminal c;
        c.loadCriminals(file1);
        if(!file1) break;
        criminals.push_back(c);
    }

    // --- Load Family ---
    while(true){
        Family m;
        m.loadFamilyMember(file2);
        if(!file2 || m.getCodename().empty())
            break;
        family.push_back(m);
    }



    // --- Load Batsuit parts ---
    while(true){
        Batsuit b;
        b.loadBatsuit(file3);
        if(!file3) break;
        suit.push_back(b);
    }

    /*
    std::cout << "\n=== Criminal Database ===\n";
    for(const auto& c : criminals)
        std::cout << c << "\n";

    std::cout << "\n=== Bat-Family Members ===\n";
    for(const auto& m : family)
        std::cout << m << "\n";

    std::cout << "\n=== Batsuit Loadout ===\n";
    for(const auto& b : suit)
        std::cout << b << "\n";
*/

        // --- MENIU ---
    int choice = -1;
    while(choice != 0)
    {
        std::cout << "\n==========================\n";
        std::cout << "        BAT-COMPUTER      \n";
        std::cout << "==========================\n";
        std::cout << "1) Show Criminal Database\n";
        std::cout << "2) Show Bat-Family Members\n";
        std::cout << "3) Show Batsuit Loadout\n";
        std::cout << "4) Search Criminal by Name\n";
        std::cout << "5) Search Family Member by Codename\n";
        std::cout << "0) Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice)
        {
            case 1:
                std::cout << "\n=== Criminal Database ===\n";
                for(const auto& c : criminals)
                    std::cout << c << "\n";
                break;

            case 2:
                std::cout << "\n=== Bat-Family Members ===\n";
                for(const auto& m : family)
                    std::cout << m << "\n";
                break;

            case 3:
                std::cout << "\n=== Batsuit Loadout ===\n";
                for(const auto& b : suit)
                    std::cout << b << "\n";
                break;

            case 4:
            {
                std::cout << "\nEnter criminal name: ";
                std::string searchName;
                std::getline(std::cin, searchName);

                bool found = false;
                for(const auto& c : criminals)
                {
                    if(c.getName() == searchName)
                    {
                        std::cout << "\nFOUND:\n" << c << "\n";
                        found = true;
                    }
                }
                if(!found) std::cout << "No criminal found with that name.\n";
                break;
            }

            case 5:
            {
                std::cout << "\nEnter codename: ";
                std::string code;
                std::getline(std::cin, code);

                bool found = false;
                for(const auto& m : family)
                {
                    if(m.getCodename() == code)
                    {
                        std::cout << "\nFOUND:\n" << m << "\n";
                        found = true;
                    }
                }
                if(!found) std::cout << "No family member found.\n";
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
