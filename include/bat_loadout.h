#ifndef BAT_LOADOUT_H
#define BAT_LOADOUT_H

#include <vector>
#include <memory>
#include <iostream>
#include "igadget.h"
#include "batsuit.h"
#include "ibatsuit.h"

class BatLoadout {
private:
    std::vector<std::unique_ptr<IGadget>> gadgets;
    std::vector<Batsuit> suits; // keep existing parts
    std::vector<std::unique_ptr<IBatsuit>> fullSuits; // polymorphic full suits
    size_t activeSuitIndex = 0;
public:
    BatLoadout() = default;
    ~BatLoadout() = default;

    void addGadget(std::unique_ptr<IGadget> g) {
        gadgets.push_back(std::move(g));
    }

    void useGadget(size_t idx) {
        if(idx >= gadgets.size()) {
            std::cout << "No such gadget slot.\n";
            return;
        }
        gadgets[idx]->activate();
    }

    void addSuitPart(const Batsuit& part) {
        suits.push_back(part);
    }

    void equipFullSuit(std::unique_ptr<IBatsuit> s) {
        fullSuits.push_back(std::move(s));
    }

    void applyDamageToActiveSuit(int dmg) {
        if(!fullSuits.empty()) {
            fullSuits[activeSuitIndex]->applyDamage(dmg);
            return;
        }
        if(suits.empty()) return;
        suits[activeSuitIndex].applyBattleDamage(dmg);
    }

    void listGadgets() const {
        std::cout << "Gadgets: \n";
        for(const auto& g : gadgets) std::cout << " - " << g->name() << "\n";
    }
};

#endif // BAT_LOADOUT_H

