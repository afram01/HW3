#include "item.h"

#include <bits/stdc++.h>

Item::Item(const std::string &name, double price, int available, const char *unit)
    : name(name), price(price), available(available), unit(unit)
{
    if (price < 0)
    {
        throw std::invalid_argument("Price cannot be negative");
    }
    if (available < 0)
    {
        throw std::invalid_argument("Available cannot be negative");
    }
}

std::string Item::getName() const { return name; }
double Item::getPrice() const { return price; }
int Item::getAvailable() const { return available; }
std::string Item::getUnit() const { return unit; }

void Item::setName(std::string &newname) { name = newname; }
void Item::setPrice(double newprice)
{
    if (newprice >= 0)
    {
        price = newprice;
    }
    else
    {
        throw std::invalid_argument("Price cannot be negative");
    }
}
void Item::setAvailable(int newava)
{
    if (newava >= 0)
    {
        available = newava;
    }
    else
    {
        throw std::invalid_argument("Available cannot be negative");
    }
}

Item &Item::operator++()
{
    ++available;
    return *this;
}
Item &Item::operator--()
{
    if (available == 0)
    {
        throw std::runtime_error("Available is 0 and cannot be decremented");
    }
    --available;
    return *this;
}
Item &Item::operator+(int amount)
{
    if (amount < 0 && available < -amount)
    {
        throw std::runtime_error("Cannot reduce available below 0");
    }
    available += amount;
    return *this;
}
Item &Item::operator-(int amount)
{
    if (amount < 0 || available < amount)
    {
        throw std::runtime_error("Cannot reduce available below 0");
    }
    available -= amount;
    return *this;
}

bool Item::operator==(const Item &other) const
{
    return name == other.name && price == other.price && available == other.available && unit == other.unit;
}
bool Item::operator!=(const Item &other) const
{
    return !(*this == other);
}

double Item::priceEnd(int quantity) const
{
    int free_items = quantity / 5;
    return price * (quantity - free_items);
}

std::ostream &operator<<(std::ostream &output, const Item &item)
{
    output << std::fixed << std::setprecision(2) << item.price << " USD per " << item.unit;
    return output;
}

Fruit::Fruit(const std::string &name, double price, int available)
    : Item(name, price, available, "kg") {}
std::unique_ptr<Item> Fruit::clone() const
{
    return std::make_unique<Fruit>(*this);
}
void Fruit::show() const
{
    std::cout << "Fruit: " << getName() << "\nPrice (per kg): " << getPrice() << " USD\n";
}
double Fruit::priceEnd(int quantity) const
{
    return Item::priceEnd(quantity);
}

Snack::Snack(const std::string &name, double price, int available)
    : Item(name, price, available, "pack") {}
std::unique_ptr<Item> Snack::clone() const
{
    return std::make_unique<Snack>(*this);
}
void Snack::show() const
{
    std::cout << "Snack: " << getName() << "\nPrice (per pack): " << getPrice() << " USD\n";
}
double Snack::priceEnd(int quantity) const
{
    return Item::priceEnd(quantity);
}

Seaso::Seaso(const std::string &name, double price, int available)
    : Item(name, price, available, "g") {}
std::unique_ptr<Item> Seaso::clone() const
{
    return std::make_unique<Seaso>(*this);
}
void Seaso::show() const
{
    std::cout << "Seasoning: " << getName() << "\nPrice (per g): " << getPrice() << " USD\n";
}
double Seaso::priceEnd(int quantity) const
{
    return Item::priceEnd(quantity);
}
