// Batman.cpp

#include "batman.h"

using namespace std;

Batman::Batman(string alias_, const Batsuit& suit_,
       const vector<Family>& allies_,
       const vector<Criminal>& enemies_)
    : alias(std::move(alias_)), suit(suit_), allies(allies_), enemies(enemies_) {}

ostream& operator<<(ostream& os, const Batman& b) {
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