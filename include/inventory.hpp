#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class Inventory {
protected:
    std::vector<T> items;
    std::string categoryName;
public:
    explicit Inventory(std::string name) : categoryName(std::move(name)) {}

    void addItem(const T& item) {
        items.push_back(item);
    }

    template <typename Predicate>
    T* findItem(Predicate p) {
        auto it = std::find_if(items.begin(), items.end(), p);
        if (it != items.end()) return &*it;
        return nullptr;
    }

    void displayInventory() const {
        std::cout << "\n--- INVENTORY: " << categoryName << " ---\n";
        for (const auto& item : items) {
            std::cout << " - " << item << "\n";
        }
    }

    [[nodiscard]] size_t getCount() const { return items.size(); }
};

#endif

