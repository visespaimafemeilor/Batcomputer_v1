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
#include "crimeLord.h"

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

        std::ifstream fin("database.txt");
        int total;
        if(fin >> total) {
            for(int i = 0; i < total; ++i) {
                auto obj = DatabaseEntry::createFromStream(fin);
                if(obj) database.push_back(obj);
            }
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
            case 0: {
                    std::ofstream fout("database.txt");
                    if (fout) {
                        fout << database.size() << "\n";
                        for (const auto& entry : database) {
                            entry->save(fout);
                        }
                        fout.close();
                        std::cout << "Database saved successfully.\n";
                    }
                    std::cout << "\nExiting Bat-Computer... Stay vigilant.\n";
                    break;
            }
            case 1: {
                    std::cout << "\n=== Criminal Database (Inmates) ===\n";
                    bool foundAny = false;
                    for (const auto& e : database) {
                        if (auto c = std::dynamic_pointer_cast<Criminal>(e)) {
                            foundAny = true;
                            std::cout << "ID: " << c->getId() << "\n";
                            std::cout << "Codename: " << c->getName() << "\n";
                            std::cout << "Type: " << c->type() << "\n";
                            std::cout << "Rank: " << c->getRank() << "\n";
                            std::cout << "Intel count: " << c->getIntel().size() << "\n";
                            std::cout << "Threat Level: " << c->calculateThreatLevel() << "\n";

                            std::string spec = c->specialty();
                            if(!spec.empty()) std::cout << "Specialty: " << spec << "\n";

                            std::cout << "--------------------------\n";
                        }
                    }
                    if (!foundAny) std::cout << "No criminal records found in database.\n";
                    break;
            }

            case 2: {
                        std::cout << "\n=== Bat-Family Members ===\n";
                        bool foundAny = false;
                        for (const auto& e : database) {
                            if (auto f = std::dynamic_pointer_cast<Family>(e)) {
                                foundAny = true;
                                std::cout << "Codename: " << f->getCodename() << "\n";
                                std::cout << "Civilian Name: " << f->getCivilianName() << "\n";
                                std::cout << "Physical Power: " << f->getPhysicalPower() << "\n";
                                std::cout << "Skills: ";
                                const auto& skills = f->getSkills();
                                for (size_t i = 0; i < skills.size(); ++i) {
                                    std::cout << skills[i] << (i == skills.size() - 1 ? "" : ", ");
                                }
                                std::cout << "\n--------------------------\n";
                            }
                        }
                        if (!foundAny) std::cout << "No family members found in database.\n";
                        break;
            }

            case 3: {
                        std::cout << "\n=== Batsuit Loadout ===\n";
                        bool foundAny = false;
                        for (const auto& e : database) {
                            // Încercăm să convertim intrarea la tipul Batsuit
                            if (auto b = std::dynamic_pointer_cast<Batsuit>(e)) {
                                foundAny = true;
                                std::cout << "Part: " << b->getPart() << "\n";
                                std::cout << "Level: " << b->getLevel() << "\n";
                                std::cout << "Integrity: " << b->getIntegrity() << "%\n";
                                std::cout << "Status: " << b->statusReport() << "\n";
                                std::cout << "--------------------------\n";
                            }
                        }
                        if (!foundAny) std::cout << "No batsuit parts found in database.\n";
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

            case 7: {
                    std::string codename, cname;
                    std::cout << "\nChoose family member (codename): "; std::getline(std::cin, codename);
                    std::cout << "Choose criminal: "; std::getline(std::cin, cname);

                    std::shared_ptr<Family> vigilante = nullptr;
                    std::shared_ptr<Criminal> enemy = nullptr;

                    for(auto& e : database) {
                        if(!vigilante) vigilante = std::dynamic_pointer_cast<Family>(e);
                        if(vigilante && vigilante->getCodename() != codename) vigilante = nullptr;

                        if(!enemy) enemy = std::dynamic_pointer_cast<Criminal>(e);
                        if(enemy && enemy->getName() != cname) enemy = nullptr;
                    }

                    if(vigilante && enemy) {
                        std::cout << vigilante->fightReport(*enemy);
                        std::cout << vigilante->simulateBattle(*enemy);
                    } else {
                        std::cout << "One or both entities not found.\n";
                    }
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

            case 9: {
                    std::cout << "\nEnter criminal name to promote: ";
                    std::string name; std::getline(std::cin, name);
                    bool found = false;
                    for(auto& e : database) {
                        if(auto c = std::dynamic_pointer_cast<Criminal>(e)) {
                            if(c->getName() == name) {
                                c->promote();
                                std::cout << "Criminal promoted! New Rank: " << c->getRank() << "\n";
                                found = true; break;
                            }
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
