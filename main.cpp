#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include "criminals.h"
#include "family.h"
#include "batsuit.h"
#include "batman.h"

int main(){

    std::cout<<"Welcome, Dark Knight!\n";

    std::vector<Criminal> criminals;
    criminals.reserve(20);
    std::vector<Family> family;
    family.reserve(20);
    std::vector<Batsuit> suit;
    suit.reserve(20);

    std::vector<Batman*> database;

    std::ifstream file1("criminals.txt");
    std::ifstream file2("family.txt");
    std::ifstream file3("batsuit.txt");

    if(!file1 || !file2 || !file3){
        std::cerr << "One or more files could not be opened.\n";
        return 1;
    }

    while(true) {
        Criminal c;
        if(!c.loadCriminal(file1)) break;
        criminals.push_back(c);
    }
    for(auto & criminal : criminals) {
        database.push_back(&criminal);
    }

    while(true) {
        Family m;
        if(!m.loadFamilyMember(file2)) break;
        family.push_back(m);
    }
    for(auto & i : family) {
        database.push_back(&i);
    }

    while(true) {
        Batsuit b;
        if(!b.loadBatsuit(file3)) break;
        suit.push_back(b);
    }
    for(auto & i : suit) {
        database.push_back(&i);
    }

    std::cout << "[SYSTEM ONLINE] Welcome, Dark Knight.\n";
    std::cout << "Entities loaded: " << database.size() << "\n";

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
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
            continue;
        }
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
                if (!(std::cin >> securityLevel)) {
                    std::cout << "Invalid security level entered.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
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