#include "Wallet.hpp"

Wallet::Wallet(double balance): balance_(balance), kInitialBalance(balance) {}

void Wallet::updateBalance(double change) noexcept {
    balance_ += change * balance_;
}

WalletSnapshot Wallet::getSnapshot() const noexcept {
    return WalletSnapshot {
        kInitialBalance,
        balance_,
        balance_ - kInitialBalance
    };
}

void Wallet::reset() noexcept {
    balance_ = kInitialBalance;
}