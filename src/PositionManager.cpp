#include "PositionManager.hpp"
#include <iostream>

PositionManager::PositionManager(Wallet& wallet) : wallet_(wallet) {};

bool PositionManager::openPosition(double price){
    std::cout << "Position open with price " << price << std::endl;
    return true;
}

bool PositionManager::closePosition(double price){
    std::cout << "Position close with price " << price << std::endl;
    return true;
}