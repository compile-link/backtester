#include "Wallet.hpp"

Wallet::Wallet(double balance): balance_(balance) {}

bool Wallet::updateBalance(double priceChange, double sizeFactor) {
    balance_ += sizeFactor * priceChange * balance_;

    return true;
}