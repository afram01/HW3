#include "currency.h"
#include "item.h"
#include "shopping.h"
#include "bank.h"

#include <bits/stdc++.h>
int main() {
    // پیام خوش‌آمدگویی
    std::cout << "Welcome to Marklar's International Shop!\n\n";

    // ایجاد لیست محصولات
    std::vector<std::unique_ptr<Item>> items;
    items.push_back(std::make_unique<Fruit>("Apple", 2.5, 10));
    items.push_back(std::make_unique<Fruit>("Tomato", 2, 10));
    items.push_back(std::make_unique<Fruit>("Banana", 3 , 15));
    items.push_back(std::make_unique<Fruit>("Pear", 2.2 , 20));
    items.push_back(std::make_unique<Snack>("Chips", 1.5, 20));
    items.push_back(std::make_unique<Snack>("Puffed snack", 1.5, 20));
    items.push_back(std::make_unique<Snack>("Lavashak", 1.5, 20));
    items.push_back(std::make_unique<Seaso>("turmeric", 1.5, 200));
    items.push_back(std::make_unique<Seaso>("Salt", 0.01, 100));
    items.push_back(std::make_unique<Seaso>("Pepper", 0.5 , 150));

    // ایجاد حساب‌های بانکی
    auto customer_balance = std::make_unique<USD>(1000.0);
    BankAccount customer("Customer", "C123", AccountType::personal, std::move(customer_balance));
    auto shop_balance = std::make_unique<USD>(10000.0);
    BankAccount shop("Shop", "S456", AccountType::organization, std::move(shop_balance));

    // ایجاد سبد خرید
    ShoppingCart cart;

    char continue_shopping = 'y';
    while (continue_shopping == 'y' || continue_shopping == 'Y') {
        // نمایش محصولات موجود
        std::cout << "Available Products:\n";
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i]->getName() << " - "
                      << *items[i] << " (Available: " << items[i]->getAvailable() << ")\n";
        }

        // دریافت انتخاب محصول
        std::cout << "\nWhich product would you like to buy? (Enter number): ";
        size_t choice;
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > items.size()) {
            std::cout << "Invalid selection. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // دریافت تعداد
        std::cout << "How many " << items[choice - 1]->getUnit() << " would you like to buy? ";
        int quantity;
        std::cin >> quantity;
        if (std::cin.fail() || quantity <= 0 || quantity > items[choice - 1]->getAvailable()) {
            std::cout << "Invalid quantity or insufficient stock. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // ذخیره موجودی اولیه برای برگرداندن در صورت خطا
        int initial_available = items[choice - 1]->getAvailable();

        // افزودن به سبد خرید
        try {
            auto item_clone = items[choice - 1]->clone(); // ایجاد کپی جدید با clone
            cart.addItem(std::move(item_clone), quantity); // انتقال کپی به سبد خرید
            // کاهش موجودی اصلی پس از موفقیت
            items[choice - 1]->setAvailable(initial_available - quantity);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            // برگرداندن موجودی در صورت خطا
            items[choice - 1]->setAvailable(initial_available);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // نمایش سبد خرید
        std::cout << "\nCurrent cart:\n" << cart;

        // دریافت نوع ارز
        std::cout << "\nSelect currency for payment:\n1. USD\n2. EUR\n3. IRR\nEnter number: ";
        int currency_choice;
        std::cin >> currency_choice;
        std::unique_ptr<Currency> payment;
        double total_cost = cart.calculateTotal();
        switch (currency_choice) {
            case 1:
                payment = std::make_unique<USD>(total_cost);
                break;
            case 2:
                payment = std::make_unique<EUR>(total_cost / EUR::conversion_rate_to_USD);
                break;
            case 3:
                payment = std::make_unique<IRR>(total_cost / IRR::conversion_rate_to_USD);
                break;
            default:
                std::cout << "Invalid currency choice. Try again.\n";
                cart.clearCart();
                continue;
        }

        // پردازش تراکنش
        try {
            customer.transfer(shop, *payment, "Purchase");
            std::cout << "Purchase successful! Paid " << *payment << ".\n";
            std::cout << "Current balance: " << customer.getBalance() << "\n";
            cart.clearCart();
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            cart.clearCart();
            continue;
        }

        // پرس‌وجو برای ادامه خرید
        std::cout << "\nWould you like to make another purchase? (y/n): ";
        std::cin >> continue_shopping;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Thank you for shopping at Marklar's International Shop! Goodbye.\n";
    return 0;
}
