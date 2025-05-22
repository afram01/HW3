#include "shopping.h"

#include <bits/stdc++.h>

ShoppingCart::ShoppingCart(){

}

void ShoppingCart::addItem(std::unique_ptr<Item> item, int quantity) {
    if (item->getAvailable() < quantity) {
        throw std::runtime_error("Not enough stock for " + item->getName());
    }
    item->setAvailable(item->getAvailable() - quantity);

    auto it = std::find_if(items.begin(), items.end(),
        [&item](const auto& i) { return i->getName() == item->getName(); });
    if (it != items.end()) {
        int index = std::distance(items.begin(), it);
        quantities[index] += quantity;
        freeItems[index] = quantities[index] / 5;
    } else {
        items.push_back(std::move(item));
        quantities.push_back(quantity);
        freeItems.push_back(quantity / 5);
    }
}

void ShoppingCart::removeItem(const std::string& itemName) {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemName](const auto& i) { return i->getName() == itemName; });
    if (it != items.end()) {
        int index = std::distance(items.begin(), it);
        (*it)->setAvailable((*it)->getAvailable() + quantities[index]);
        items.erase(items.begin() + index);
        quantities.erase(quantities.begin() + index);
        freeItems.erase(freeItems.begin() + index);
    } else {
        throw std::runtime_error("Item " + itemName + " not found in cart.");
    }
}

double ShoppingCart::calculateTotal() const {
    double total = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        total += items[i]->priceEnd(quantities[i]);
    }
    return total;
}

void ShoppingCart::displayCart() const {
    std::cout << "Cart contents:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "- " << items[i]->getName() << ": " << quantities[i] << " " << items[i]->getUnit()
                  << " (" << freeItems[i] << " free, $" << std::fixed << std::setprecision(2)
                  << items[i]->priceEnd(quantities[i]) << ")\n";
    }
    std::cout << "Total: $" << std::fixed << std::setprecision(2) << calculateTotal() << "\n";
}

void ShoppingCart::clearCart() {
    for (size_t i = 0; i < items.size(); ++i) {
        items[i]->setAvailable(items[i]->getAvailable() + quantities[i]);
    }
    items.clear();
    quantities.clear();
    freeItems.clear();
}

int ShoppingCart::getItemCount() const {
    return items.size();
}

std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart) {
    cart.displayCart();
    return os;
}

ShoppingCart& ShoppingCart::operator++() {
    if (!items.empty()) {
        quantities.back()++;
        freeItems.back() = quantities.back() / 5;
        items.back()->setAvailable(items.back()->getAvailable() - 1);
    } else {
        throw std::runtime_error("Cannot increment empty cart");
    }
    return *this;
}

ShoppingCart &ShoppingCart::operator++(int) {
    ShoppingCart& temp = (*this);
    ++(*this);
    return temp;
}