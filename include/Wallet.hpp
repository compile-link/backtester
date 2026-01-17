#pragma once

class Wallet {
    public:
        explicit Wallet(double balance = kDefaultInitialBalance);
        bool updateBalance(double priceChange, double sizeFactor);

    private:
        static constexpr double kDefaultInitialBalance = 10000;
        const double kInitialBalance;
        double balance_;
};