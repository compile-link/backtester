#pragma once

struct WalletSnapshot {
    double initialBalance;
    double endBalance;
    double pnL;         
};

class Wallet {
    public:
        explicit Wallet(double balance = kDefaultInitialBalance);
        bool updateBalance(double priceChange, double sizeFactor);
        WalletSnapshot getSnapshot() const noexcept;

    private:
        static constexpr double kDefaultInitialBalance = 10000;
        const double kInitialBalance;
        double balance_;
};