#ifndef IGADGET_H
#define IGADGET_H

#include <string>
#include <memory>

class IGadget {
public:
    virtual ~IGadget() = default;
    virtual void activate() = 0;
    [[nodiscard]] virtual std::string name() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IGadget> clone() const = 0;
};

#endif // IGADGET_H

