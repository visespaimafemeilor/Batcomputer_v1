#ifndef EMP_DEVICE_H
#define EMP_DEVICE_H

#include "igadget.h"
#include <iostream>

class EMPDevice : public IGadget {
private:
    int charges = 1;
public:
    explicit EMPDevice(int c = 1) : charges(c) {}
    ~EMPDevice() override = default;

    void activate() override {
        if(charges <= 0) {
            std::cout << "EMPDevice: no charges left.\n";
            return;
        }
        --charges;
        std::cout << "EMPDevice activated! (remaining charges: " << charges << ")\n";
    }

    [[nodiscard]] std::string name() const override { return {"EMPDevice"}; }
    [[nodiscard]] std::unique_ptr<IGadget> clone() const override { return std::make_unique<EMPDevice>(*this); }
};

#endif // EMP_DEVICE_H

