#include "batman.h"

Batman::Batman(std::string n) : name(move(n)) {}
Batman::~Batman() {}

const std::string& Batman::getName() const {
    return name;
}