#pragma once

struct WalletSnapshot {
    double initialBalance;
    double endBalance;
    double pnL;         
};

class Wallet {
    public:
        explicit Wallet(double balance = kDefaultInitialBalance);
        void updateBalance(double change) noexcept;
        WalletSnapshot getSnapshot() const noexcept;
        void reset() noexcept; 

    private:
        static constexpr double kDefaultInitialBalance = 10000.0;
        const double kInitialBalance;
        double balance_;
};