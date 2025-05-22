#ifndef CURRENCY_H
#define CURRENCY_H

#include <bits/stdc++.h>

class Currency {
protected:
    double value;
    std::string type;
public:
    Currency(double val = 0.0, const std::string& tp = "Currency");
    virtual ~Currency() = default;
    double getValue() const;
    std::string getType() const;
    virtual double convertTo(const std::string& target_type) const;

    std::unique_ptr<Currency> operator+(const Currency& other) const;
    std::unique_ptr<Currency> operator-(const Currency& other) const;
    std::unique_ptr<Currency> operator*(double factor) const;
    std::unique_ptr<Currency> operator/(double factor) const;

    bool operator==(const Currency& other) const;
    bool operator!=(const Currency& other) const;
    bool operator<(const Currency& other) const;
    bool operator>(const Currency& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Currency& currency);
};

class USD : public Currency {
public:
    static constexpr double conversion_rate_to_USD = 1.0;
    USD(double val = 0.0);
    double convertTo(const std::string& target_type) const override;
};

class EUR : public Currency {
public:
    static constexpr double conversion_rate_to_USD = 1.10;
    EUR(double val = 0.0);
    double convertTo(const std::string& target_type) const override;
};

class IRR : public Currency {
public:
    static constexpr double conversion_rate_to_USD = 0.000024;
    IRR(double val = 0.0);
    double convertTo(const std::string& target_type) const override;
};

#endif