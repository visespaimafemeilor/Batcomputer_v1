#ifndef BATMAN_H
#define BATMAN_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "batsuit.h"
#include "family.h"
#include "criminals.h"

class Batman {
private:
    std::string alias;
    Batsuit suit;
    std::vector<Family> allies;
    std::vector<Criminal> enemies;

public:
    Batman(std::string alias_, const Batsuit& suit_,
           const std::vector<Family>& allies_,
           const std::vector<Criminal>& enemies_);

    friend std::ostream& operator<<(std::ostream& os, const Batman& b);
};

#endif