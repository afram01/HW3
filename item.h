#ifndef ITEM_H
#define ITEM_H

#include <bits/stdc++.h>

class Item {
    friend std::ostream& operator<<(std::ostream& output, const Item& item);
private:
    std::string name;
    double price;
    int available;
    std::string unit;
public:
    Item(const std::string& name, double price, int available, const char* unit);
    virtual ~Item() = default;

    std::string getName() const;
    double getPrice() const;
    int getAvailable() const;
    std::string getUnit() const;

    void setName(std::string& newname);
    void setPrice(double newprice);
    void setAvailable(int newava);

    Item& operator++();
    Item& operator--();
    Item& operator+(int amount);
    Item& operator-(int amount);

    bool operator==(const Item& other) const;
    bool operator!=(const Item& other) const;

    virtual void show() const = 0;
    virtual std::unique_ptr<Item> clone() const = 0;
    virtual double priceEnd(int quantity) const;
};

class Fruit : public Item {
public:
    Fruit(const std::string& name, double price, int available);
    ~Fruit() override = default;
    std::unique_ptr<Item> clone() const override;
    void show() const override;
    double priceEnd(int quantity) const override;
};

class Snack : public Item {
public:
    Snack(const std::string& name, double price, int available);
    ~Snack() override = default;
    std::unique_ptr<Item> clone() const override;
    void show() const override;
    double priceEnd(int quantity) const override;
};

class Seaso : public Item {
public:
    Seaso(const std::string& name, double price, int available);
    ~Seaso() override = default;
    std::unique_ptr<Item> clone() const override;
    void show() const override;
    double priceEnd(int quantity) const override;
};

#endif
