#ifndef BATARANG_H
#define BATARANG_H

#include "igadget.h"
#include <iostream>

class Batarang : public IGadget {
public:
    Batarang() = default;
    ~Batarang() override = default;

    void activate() override {
        std::cout << "[Batarang] Thrown: target hit with non-lethal blunt force.\n";
    }

    [[nodiscard]] std::string name() const override { return "Batarang"; }
    [[nodiscard]] std::unique_ptr<IGadget> clone() const override { return std::make_unique<Batarang>(*this); }
};

#endif // BATARANG_H

