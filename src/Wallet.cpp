#include "Wallet.hpp"

Wallet::Wallet(double balance): balance_(balance), kInitialBalance(balance) {}

bool Wallet::updateBalance(double priceChange, double sizeFactor) {
    balance_ += sizeFactor * priceChange * balance_;

    return true;
}

WalletSnapshot Wallet::getSnapshot() const noexcept {
    return WalletSnapshot {
        kInitialBalance,
        balance_,
        balance_ - kInitialBalance
    };
}