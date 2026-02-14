#ifndef ICRIMINAL_SPECIALIST_H
#define ICRIMINAL_SPECIALIST_H

#include <string>

class ISpecialist {
public:
    virtual ~ISpecialist() = default;
    [[nodiscard]] virtual std::string specialty() const = 0;
};

#endif // ICRIMINAL_SPECIALIST_H

