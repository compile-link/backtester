#include "PositionManager.hpp"
#include <iostream>

PositionManager::PositionManager() {
    longPosition_.type = PositionType::Long;
    shortPosition_.type = PositionType::Short;
};

bool PositionManager::openLong(double price, double sizeFactor){
    return openPosition_(longPosition_, price, sizeFactor);
}

bool PositionManager::openShort(double price, double sizeFactor){
    return openPosition_(shortPosition_, price, sizeFactor);
}

bool PositionManager::closeLong(double price){
    return closePosition_(longPosition_, price);
}

bool PositionManager::closeShort(double price){
    return closePosition_(shortPosition_, price);
}

bool PositionManager::openPosition_(Position& position, double price, double sizeFactor) {
    if (position.isOpen){ 
        // std::cout << "Not opening new position, already open\n";
        return false;
    }

    // std::cout << "Opening new position\n";
    position.isOpen = true;
    position.openPrice = price;
    position.sizeFactor = sizeFactor;

    return true;
}

bool PositionManager::closePosition_(Position& position, double price){
    if (!position.isOpen){
        // std::cout << "Not closing position, already closed\n";
        return false;
    }

    // std::cout << "Closing position\n";
    position.isOpen = false;
    position.closePrice = price;
    tradeCount_++;
    if(position.openPrice < position.closePrice)
        if(position.type == PositionType::Long) winCount_++;
        else lossCount_++; 

    if(position.openPrice > position.closePrice)
        if(position.type == PositionType::Long) lossCount_++;
        else winCount_++; 

    return wallet_.updateBalance(position.priceChangePercentage(), position.sizeFactor);
}

PositionManagerSnapshot PositionManager::getSnapshot() const noexcept {
    return PositionManagerSnapshot {
        tradeCount_,
        winCount_,
        lossCount_
    };
}

WalletSnapshot PositionManager::getWalletSnapshot() const noexcept {
    return wallet_.getSnapshot(); 
}
