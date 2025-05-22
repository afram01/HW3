#include "currency.h"

#include <bits/stdc++.h>

Currency::Currency(double val, const std::string& tp) : value(val), type(tp) {}
double Currency::getValue() const { return value; }
std::string Currency::getType() const { return type; }

double Currency::convertTo(const std::string& target_type) const {
    if (target_type == type) return value;
    throw std::invalid_argument("Conversion not supported for base Currency class: " + target_type);
}

std::unique_ptr<Currency> Currency::operator+(const Currency& other) const {
    double other_val_in_usd = other.convertTo("USD");
    double result_in_usd = convertTo("USD") + other_val_in_usd;
    return std::make_unique<USD>(result_in_usd);
}

std::unique_ptr<Currency> Currency::operator-(const Currency& other) const {
    double other_val_in_usd = other.convertTo("USD");
    double result_in_usd = convertTo("USD") - other_val_in_usd;
    return std::make_unique<USD>(result_in_usd);
}

std::unique_ptr<Currency> Currency::operator*(double factor) const {
    return std::make_unique<Currency>(value * factor, type);
}

std::unique_ptr<Currency> Currency::operator/(double factor) const {
    if (factor == 0) throw std::invalid_argument("Division by zero");
    return std::make_unique<Currency>(value / factor, type);
}

bool Currency::operator==(const Currency& other) const {
    return std::abs(convertTo("USD") - other.convertTo("USD")) < 1e-9;
}

bool Currency::operator!=(const Currency& other) const { return !(*this == other); }
bool Currency::operator<(const Currency& other) const {
    return convertTo("USD") < other.convertTo("USD");
}
bool Currency::operator>(const Currency& other) const {
    return convertTo("USD") > other.convertTo("USD");
}

std::ostream& operator<<(std::ostream& os, const Currency& currency) {
    os << std::fixed << std::setprecision(2) << currency.value << " " << currency.type;
    return os;
}

USD::USD(double val) : Currency(val, "USD") {}
double USD::convertTo(const std::string& target_type) const {
    if (target_type == "USD") return value;
    if (target_type == "EUR") return value / EUR::conversion_rate_to_USD;
    if (target_type == "IRR") return value / IRR::conversion_rate_to_USD;
    throw std::invalid_argument("Unsupported currency type: " + target_type);
}

EUR::EUR(double val) : Currency(val, "EUR") {}
double EUR::convertTo(const std::string& target_type) const {
    if (target_type == "EUR") return value;
    if (target_type == "USD") return value * conversion_rate_to_USD;
    if (target_type == "IRR") {
        double usd_val = value * conversion_rate_to_USD;
        return usd_val / IRR::conversion_rate_to_USD;
    }
    throw std::invalid_argument("Unsupported currency type: " + target_type);
}

IRR::IRR(double val) : Currency(val, "IRR") {}
double IRR::convertTo(const std::string& target_type) const {
    if (target_type == "IRR") return value;
    if (target_type == "USD") return value * conversion_rate_to_USD;
    if (target_type == "EUR") {
        double usd_val = value * conversion_rate_to_USD;
        return usd_val / EUR::conversion_rate_to_USD;
    }
    throw std::invalid_argument("Unsupported currency type: " + target_type);
}