#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <memory>
#include "criminals.h"
#include "family.h"
#include "batsuit.h"
#include "database_entry.h"
#include "exceptions.h"
#include "emp_device.h"
#include "bat_loadout.h"
#include "stealth_suit.h"
#include "bank_robber.h"
#include "hacker.h"
#include "mastermind.h"

int main(){
    try {
        std::cout<<"Welcome, Dark Knight!\n";

        std::vector<Criminal> criminals;
        criminals.reserve(20);
        std::vector<Family> family;
        family.reserve(20);
        std::vector<Batsuit> suit;
        suit.reserve(20);

        std::vector<std::shared_ptr<DatabaseEntry>> database;

        std::ifstream file1("criminals.txt");
        std::ifstream file2("family.txt");
        std::ifstream file3("batsuit.txt");

        if(!file1) throw FileLoadException("criminals.txt");
        if(!file2) throw FileLoadException("family.txt");
        if(!file3) throw FileLoadException("batsuit.txt");

        while(true) {
            Criminal c;
            if(!c.loadCriminal(file1)) break;
            criminals.push_back(c);
        }
        for(auto& criminal : criminals) {
            database.push_back(std::make_shared<Criminal>(criminal));
        }

        while(true) {
            Family m;
            if(!m.loadFamilyMember(file2)) break;
            family.push_back(m);
        }
        for(auto& i : family) {
            database.push_back(std::make_shared<Family>(i));
        }

        while(true) {
            Batsuit b;
            if(!b.loadBatsuit(file3)) break;
            suit.push_back(b);
        }
        for(auto& i : suit) {
            database.push_back(std::make_shared<Batsuit>(i));
        }

        // add example specialized criminals to the polymorphic database
        database.push_back(std::make_shared<BankRobber>(101, std::string("Vault King"), 5, std::vector<std::string>{"vault map","timing"}));
        database.push_back(std::make_shared<Hacker>(102, std::string("ZeroDay"), 4, std::vector<std::string>{"exploit","credentials"}));
        database.push_back(std::make_shared<Mastermind>(103, std::string("Professor X"), 9, std::vector<std::string>{"plan A","contacts"}));

        // small gadget demo using BatLoadout (composition)
        BatLoadout loadout;
        auto emp = std::make_unique<EMPDevice>();
        loadout.addGadget(std::move(emp));

        // create a StealthSuit from first available parts (if any)
        std::vector<Batsuit> partsForStealth;
        if(suit.size() >= 2) {
            partsForStealth.push_back(suit[0]);
            partsForStealth.push_back(suit[1]);
        } else if(!suit.empty()) {
            partsForStealth.push_back(suit[0]);
        }
        if(!partsForStealth.empty()) {
            loadout.equipFullSuit(std::make_unique<StealthSuit>(std::move(partsForStealth)));
        }

        std::cout << "[SYSTEM ONLINE] Welcome, Dark Knight.\n";
        std::cout << "Entities loaded: " << database.size() << "\n";
        std::cout << "Criminals: " << Criminal::getCriminalCount() << " | Family: " << Family::getFamilyMemberCount()
                  << " | Suit parts: " << Batsuit::getSuitPartCount() << " | Total: " << DatabaseEntry::getTotalEntities() << "\n";

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
            std::cout << "11) Show database polymorphically (displayInfo + assessThreat)\n";
            std::cout << "12) Demo dynamic_pointer_cast (type-specific actions)\n";
            std::cout << "13) Demo Batman gadget (EMP)\n";
            std::cout << "14) Interact two database entries (polymorphic)\n";
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

                case 11: {
                    std::cout << "\n=== Polymorphic Database View ===\n";
                    for(const auto& e : database){
                        e->displayInfo();
                        std::cout << "Threat: " << e->assessThreat() << "\n";
                    }
                    break;
                }

                case 12: {
                    std::cout << "\n=== Dynamic cast demo ===\n";
                    for(const auto& e : database){
                        // try as Criminal
                        if(auto cr = std::dynamic_pointer_cast<Criminal>(e)){
                            std::cout << "Criminal found: " << cr->getName() << " Threat: " << cr->calculateThreatLevel() << "\n";
                            continue;
                        }
                        if(auto f = std::dynamic_pointer_cast<Family>(e)){
                            std::cout << "Family member: " << f->getCodename() << " Power: " << f->getPhysicalPower() << "\n";
                            continue;
                        }
                        if(auto b = std::dynamic_pointer_cast<Batsuit>(e)){
                            std::cout << "Batsuit part: " << b->getPart() << " Integrity: " << b->getIntegrity() << "\n";
                            continue;
                        }
                        std::cout << "Unknown entry: " << e->summary() << "\n";
                    }
                    break;
                }

                case 14: {
                    std::cout << "\n=== Polymorphic interact demo ===\n";
                    if(database.empty()){
                        std::cout << "Database is empty.\n";
                        break;
                    }
                    std::cout << "Entries:\n";
                    for(size_t i = 0; i < database.size(); ++i){
                        std::cout << i << ") [" << database[i]->type() << "] " << database[i]->summary() << "\n";
                    }
                    std::cout << "Select first index: ";
                    int i1 = -1; if(!(std::cin >> i1)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); break; }
                    std::cout << "Select second index: ";
                    int i2 = -1; if(!(std::cin >> i2)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); break; }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(i1 < 0 || i2 < 0 || (size_t)i1 >= database.size() || (size_t)i2 >= database.size()){
                        std::cout << "Invalid indices.\n";
                        break;
                    }
                    std::string result = database[i1]->interact(*database[i2]);
                    std::cout << "Interaction result: " << result << "\n";
                    break;
                }

                 case 13: {
                     std::cout << "\n=== Batman gadget demo ===\n";
                     loadout.listGadgets();
                     loadout.useGadget(0);
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
    catch(const BatcomputerException& e){
        std::cerr << "Batcomputer error: " << e.what() << "\n";
        return 2;
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << "\n";
        return 3;
    }
}

