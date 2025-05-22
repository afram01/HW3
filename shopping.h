#ifndef SHOPPING_H
#define SHOPPING_H

#include <bits/stdc++.h>

#include "item.h"

class ShoppingCart {
private:
    std::vector<std::unique_ptr<Item>> items;
    std::vector<int> quantities;
    std::vector<int> freeItems;

public:
    ShoppingCart();
    void addItem(std::unique_ptr<Item> item, int quantity);
    void removeItem(const std::string& itemName);
    double calculateTotal() const;
    void displayCart() const;
    void clearCart();
    int getItemCount() const;

    ShoppingCart& operator++();
    ShoppingCart& operator++(int);
    friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart);

    ShoppingCart(const ShoppingCart&) = delete;
    ShoppingCart& operator=(const ShoppingCart&) = delete;
};

#endif
