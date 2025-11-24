#ifndef BATMAN_H
#define BATMAN_H

#include <string>
#include <iostream>
#include <utility>

class Batman {
protected:
    std::string name;

public:
    explicit Batman(std::string n = "Unknown");
    virtual ~Batman();
    [[nodiscard]] const std::string& getName() const;
    virtual void displayInfo() const = 0;
};

#endif