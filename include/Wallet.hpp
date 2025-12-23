#pragma once

class Wallet {
    public:
        explicit Wallet(double balance);

    private:
        static constexpr double kInitialBalance = 10000;
        double balance_ = kInitialBalance;
};